#!/usr/bin/env python3
"""Toy compiler frontend.

Toy is a compact competitive-programming language whose IR and optimization
pipeline are built on MLIR.  This module owns the source lexer and parser; it
does not accept C or C++ source syntax.
"""

from __future__ import annotations

import argparse
from dataclasses import dataclass
from pathlib import Path
import shutil
import subprocess
import sys
from typing import TypeAlias


class ToyError(Exception):
    """A source diagnostic with a stable location."""


@dataclass(frozen=True)
class Location:
    path: str
    line: int
    column: int

    def __str__(self) -> str:
        return f"{self.path}:{self.line}:{self.column}"


@dataclass(frozen=True)
class Token:
    kind: str
    text: str
    location: Location


KEYWORDS = {
    "break",
    "by",
    "continue",
    "else",
    "false",
    "fn",
    "for",
    "if",
    "in",
    "let",
    "return",
    "true",
    "var",
    "while",
}

OPERATORS = (
    "<<=",
    ">>=",
    "->",
    "==",
    "!=",
    "<=",
    ">=",
    "&&",
    "||",
    "<<",
    ">>",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "|=",
    "^=",
    "..=",
    "..",
    "+",
    "-",
    "*",
    "/",
    "%",
    "<",
    ">",
    "=",
    "!",
    "&",
    "|",
    "^",
)

PUNCTUATION = {"(", ")", "{", "}", "[", "]", ",", ":", ";", "."}


class Lexer:
    def __init__(self, source: str, path: str) -> None:
        self.source = source
        self.path = path
        self.offset = 0
        self.line = 1
        self.column = 1

    def lex(self) -> list[Token]:
        tokens: list[Token] = []
        while self.offset < len(self.source):
            if self._skip_trivia():
                continue
            location = self._location()
            char = self.source[self.offset]
            if char == '"':
                tokens.append(Token("string", self._lex_string(), location))
                continue
            if char == "'":
                tokens.append(Token("integer", self._lex_char(), location))
                continue
            if char.isalpha() or char == "_":
                text = self._take_while(lambda value: value.isalnum() or value == "_")
                tokens.append(Token(text if text in KEYWORDS else "identifier", text, location))
                continue
            if char.isdigit():
                text = self._take_while(lambda value: value.isdigit() or value == "_")
                if text.endswith("_") or "__" in text:
                    raise ToyError(f"{location}: malformed integer literal '{text}'")
                if (
                    self.offset + 1 < len(self.source)
                    and self.source[self.offset] == "."
                    and self.source[self.offset + 1].isdigit()
                ):
                    self._advance()
                    fraction = self._take_while(lambda value: value.isdigit() or value == "_")
                    tokens.append(Token("float", text + "." + fraction, location))
                    continue
                tokens.append(Token("integer", text, location))
                continue
            operator = next(
                (candidate for candidate in OPERATORS if self.source.startswith(candidate, self.offset)),
                None,
            )
            if operator is not None:
                self._advance(len(operator))
                tokens.append(Token(operator, operator, location))
                continue
            if char in PUNCTUATION:
                self._advance()
                tokens.append(Token(char, char, location))
                continue
            raise ToyError(f"{location}: unexpected character {char!r}")
        tokens.append(Token("eof", "", self._location()))
        return tokens

    def _skip_trivia(self) -> bool:
        if self.source[self.offset].isspace():
            self._advance()
            return True
        if self.source.startswith("//", self.offset):
            while self.offset < len(self.source) and self.source[self.offset] != "\n":
                self._advance()
            return True
        if self.source.startswith("/*", self.offset):
            start = self._location()
            self._advance(2)
            while self.offset < len(self.source) and not self.source.startswith("*/", self.offset):
                self._advance()
            if self.offset == len(self.source):
                raise ToyError(f"{start}: unterminated block comment")
            self._advance(2)
            return True
        return False

    def _take_while(self, predicate) -> str:
        start = self.offset
        while self.offset < len(self.source) and predicate(self.source[self.offset]):
            self._advance()
        return self.source[start:self.offset]

    def _lex_string(self) -> str:
        start = self._location()
        self._advance()
        result: list[str] = []
        escapes = {"0": "\0", "n": "\n", "r": "\r", "t": "\t", '"': '"', "\\": "\\"}
        while self.offset < len(self.source) and self.source[self.offset] != '"':
            char = self.source[self.offset]
            if char == "\n":
                raise ToyError(f"{start}: newline in string literal")
            if char == "\\":
                self._advance()
                if self.offset == len(self.source) or self.source[self.offset] not in escapes:
                    raise ToyError(f"{self._location()}: unsupported string escape")
                char = escapes[self.source[self.offset]]
            result.append(char)
            self._advance()
        if self.offset == len(self.source):
            raise ToyError(f"{start}: unterminated string literal")
        self._advance()
        return "".join(result)

    def _lex_char(self) -> str:
        start = self._location()
        self._advance()
        escapes = {"0": "\0", "n": "\n", "r": "\r", "t": "\t", "'": "'", "\\": "\\"}
        if self.offset == len(self.source):
            raise ToyError(f"{start}: unterminated character literal")
        char = self.source[self.offset]
        if char == "'":
            raise ToyError(f"{start}: empty character literal")
        if char == "\n":
            raise ToyError(f"{start}: newline in character literal")
        if char == "\\":
            self._advance()
            if self.offset == len(self.source) or self.source[self.offset] not in escapes:
                raise ToyError(f"{self._location()}: unsupported character escape")
            char = escapes[self.source[self.offset]]
        self._advance()
        if self.offset == len(self.source) or self.source[self.offset] != "'":
            raise ToyError(f"{start}: unterminated character literal")
        self._advance()
        return str(ord(char))

    def _advance(self, count: int = 1) -> None:
        for _ in range(count):
            char = self.source[self.offset]
            self.offset += 1
            if char == "\n":
                self.line += 1
                self.column = 1
            else:
                self.column += 1

    def _location(self) -> Location:
        return Location(self.path, self.line, self.column)


@dataclass(frozen=True)
class TypeRef:
    name: str
    arguments: tuple[TypeRef, ...]
    location: Location


@dataclass(frozen=True)
class IntegerExpr:
    value: int
    location: Location


@dataclass(frozen=True)
class FloatExpr:
    value: float
    location: Location


@dataclass(frozen=True)
class BooleanExpr:
    value: bool
    location: Location


@dataclass(frozen=True)
class StringExpr:
    value: str
    location: Location


@dataclass(frozen=True)
class NameExpr:
    name: str
    location: Location


@dataclass(frozen=True)
class UnaryExpr:
    operator: str
    operand: Expr
    location: Location


@dataclass(frozen=True)
class BinaryExpr:
    operator: str
    left: Expr
    right: Expr
    location: Location


@dataclass(frozen=True)
class AssignExpr:
    operator: str
    target: Expr
    value: Expr
    location: Location


@dataclass(frozen=True)
class CallExpr:
    callee: Expr
    arguments: tuple[Expr, ...]
    location: Location


@dataclass(frozen=True)
class IndexExpr:
    value: Expr
    index: Expr
    location: Location


@dataclass(frozen=True)
class ArrayLitExpr:
    elements: tuple[Expr, ...]
    location: Location


@dataclass(frozen=True)
class IfExpr:
    condition: Expr
    then_block: "Block"
    else_block: "Block | None"
    location: Location


Expr: TypeAlias = (
    IntegerExpr
    | FloatExpr
    | BooleanExpr
    | StringExpr
    | NameExpr
    | UnaryExpr
    | BinaryExpr
    | AssignExpr
    | CallExpr
    | IndexExpr
    | ArrayLitExpr
    | IfExpr
)


@dataclass(frozen=True)
class Block:
    statements: tuple[Stmt, ...]
    location: Location


@dataclass(frozen=True)
class VariableStmt:
    mutable: bool
    name: str
    type: TypeRef | None
    initializer: Expr
    location: Location


@dataclass(frozen=True)
class ExprStmt:
    expression: Expr
    location: Location


@dataclass(frozen=True)
class IfStmt:
    condition: Expr
    then_block: Block
    else_block: Block | None
    location: Location


@dataclass(frozen=True)
class WhileStmt:
    condition: Expr
    body: Block
    location: Location


@dataclass(frozen=True)
class ForStmt:
    name: str
    begin: Expr
    end: Expr
    step: Expr | None
    inclusive: bool
    body: Block
    location: Location


@dataclass(frozen=True)
class ReturnStmt:
    value: Expr | None
    location: Location


@dataclass(frozen=True)
class BreakStmt:
    location: Location


@dataclass(frozen=True)
class ContinueStmt:
    location: Location


Stmt: TypeAlias = VariableStmt | ExprStmt | IfStmt | WhileStmt | ForStmt | ReturnStmt | BreakStmt | ContinueStmt


@dataclass(frozen=True)
class Parameter:
    name: str
    type: TypeRef
    location: Location


@dataclass(frozen=True)
class Function:
    name: str
    parameters: tuple[Parameter, ...]
    return_type: TypeRef | None
    body: Block
    location: Location


@dataclass(frozen=True)
class Program:
    functions: tuple[Function, ...]


@dataclass(frozen=True)
class Value:
    name: str
    type: str


@dataclass(frozen=True)
class Binding:
    value: Value
    mutable: bool


BINARY_PRECEDENCE = {
    "||": 1,
    "&&": 2,
    "|": 3,
    "^": 4,
    "&": 5,
    "==": 6,
    "!=": 6,
    "<": 7,
    "<=": 7,
    ">": 7,
    ">=": 7,
    "<<": 8,
    ">>": 8,
    "+": 9,
    "-": 9,
    "*": 10,
    "/": 10,
    "%": 10,
}

ASSIGNMENT_OPERATORS = {"=", "+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "|=", "^="}


class Parser:
    def __init__(self, tokens: list[Token], require_main: bool = True) -> None:
        self.tokens = tokens
        self.index = 0
        self.require_main = require_main

    def parse_program(self) -> Program:
        functions: list[Function] = []
        while not self._at("eof"):
            functions.append(self._parse_function())
        names = [function.name for function in functions]
        if len(names) != len(set(names)):
            self._error("duplicate function definition")
        if self.require_main and "main" not in names:
            self._error("program must define fn main()")
        return Program(tuple(functions))

    def _parse_function(self) -> Function:
        start = self._expect("fn")
        name = self._expect("identifier")
        self._expect("(")
        parameters: list[Parameter] = []
        if not self._at(")"):
            while True:
                parameter_name = self._expect("identifier")
                self._expect(":")
                parameters.append(Parameter(parameter_name.text, self._parse_type(), parameter_name.location))
                if not self._match(","):
                    break
        self._expect(")")
        return_type = self._parse_type() if self._match("->") else None
        body = self._parse_block()
        return Function(name.text, tuple(parameters), return_type, body, start.location)

    def _parse_type(self) -> TypeRef:
        name = self._expect("identifier")
        arguments: list[TypeRef] = []
        if self._match("<"):
            while True:
                arguments.append(self._parse_type())
                if not self._match(","):
                    break
            self._expect(">")
        return TypeRef(name.text, tuple(arguments), name.location)

    def _parse_block(self) -> Block:
        start = self._expect("{")
        statements: list[Stmt] = []
        while not self._at("}"):
            if self._at("eof"):
                self._error("expected '}' to close block")
            statements.append(self._parse_statement())
        self._expect("}")
        return Block(tuple(statements), start.location)

    def _parse_statement(self) -> Stmt:
        if self._at("let") or self._at("var"):
            return self._parse_variable()
        if self._match("if"):
            return self._parse_if(self.tokens[self.index - 1])
        if self._match("while"):
            return self._parse_while(self.tokens[self.index - 1])
        if self._match("for"):
            return self._parse_for(self.tokens[self.index - 1])
        if self._match("return"):
            return self._parse_return(self.tokens[self.index - 1])
        if self._match("break"):
            keyword = self.tokens[self.index - 1]
            self._expect(";")
            return BreakStmt(keyword.location)
        if self._match("continue"):
            keyword = self.tokens[self.index - 1]
            self._expect(";")
            return ContinueStmt(keyword.location)
        expression = self._parse_expression()
        self._expect(";")
        return ExprStmt(expression, expression.location)

    def _parse_variable(self) -> VariableStmt:
        keyword = self._take()
        name = self._expect("identifier")
        type_ref = self._parse_type() if self._match(":") else None
        self._expect("=")
        initializer = self._parse_expression()
        self._expect(";")
        return VariableStmt(keyword.kind == "var", name.text, type_ref, initializer, keyword.location)

    def _parse_if(self, keyword: Token) -> IfStmt:
        condition = self._parse_expression()
        then_block = self._parse_block()
        else_block = None
        if self._match("else"):
            if self._match("if"):
                nested = self._parse_if(self.tokens[self.index - 1])
                else_block = Block((nested,), nested.location)
            else:
                else_block = self._parse_block()
        return IfStmt(condition, then_block, else_block, keyword.location)

    def _parse_while(self, keyword: Token) -> WhileStmt:
        condition = self._parse_expression()
        return WhileStmt(condition, self._parse_block(), keyword.location)

    def _parse_for(self, keyword: Token) -> ForStmt:
        name = self._expect("identifier")
        self._expect("in")
        begin = self._parse_expression()
        if self._match("..="):
            inclusive = True
        else:
            self._expect("..")
            inclusive = False
        end = self._parse_expression()
        step = self._parse_expression() if self._match("by") else None
        return ForStmt(name.text, begin, end, step, inclusive, self._parse_block(), keyword.location)

    def _parse_return(self, keyword: Token) -> ReturnStmt:
        value = None if self._at(";") else self._parse_expression()
        self._expect(";")
        return ReturnStmt(value, keyword.location)

    def _parse_expression(self, minimum_precedence: int = 0) -> Expr:
        expression = self._parse_unary()
        while True:
            operator = self._peek()
            precedence = BINARY_PRECEDENCE.get(operator.kind)
            if precedence is None or precedence < minimum_precedence:
                break
            self._take()
            right = self._parse_expression(precedence + 1)
            expression = BinaryExpr(operator.kind, expression, right, operator.location)
        if minimum_precedence == 0 and self._peek().kind in ASSIGNMENT_OPERATORS:
            operator = self._take()
            value = self._parse_expression()
            expression = AssignExpr(operator.kind, expression, value, operator.location)
        return expression

    def _parse_unary(self) -> Expr:
        if self._peek().kind in {"!", "-", "+"}:
            operator = self._take()
            return UnaryExpr(operator.kind, self._parse_unary(), operator.location)
        return self._parse_postfix()

    def _parse_postfix(self) -> Expr:
        expression = self._parse_primary()
        while True:
            if self._match("("):
                arguments: list[Expr] = []
                if not self._at(")"):
                    while True:
                        arguments.append(self._parse_expression())
                        if not self._match(","):
                            break
                self._expect(")")
                expression = CallExpr(expression, tuple(arguments), expression.location)
                continue
            if self._match("["):
                location = self.tokens[self.index - 1].location
                index = self._parse_expression()
                self._expect("]")
                expression = IndexExpr(expression, index, location)
                continue
            break
        return expression

    def _parse_primary(self) -> Expr:
        token = self._take()
        if token.kind == "integer":
            return IntegerExpr(int(token.text.replace("_", "")), token.location)
        if token.kind == "float":
            return FloatExpr(float(token.text.replace("_", "")), token.location)
        if token.kind in {"true", "false"}:
            return BooleanExpr(token.kind == "true", token.location)
        if token.kind == "string":
            return StringExpr(token.text, token.location)
        if token.kind == "identifier":
            return NameExpr(token.text, token.location)
        if token.kind == "if":
            return self._parse_if_expression(token)
        if token.kind == "[":
            elements: list[Expr] = []
            if not self._at("]"):
                while True:
                    elements.append(self._parse_expression())
                    if not self._match(","):
                        break
            self._expect("]")
            return ArrayLitExpr(tuple(elements), token.location)
        if token.kind == "(":
            expression = self._parse_expression()
            self._expect(")")
            return expression
        self._error("expected expression", token)

    def _parse_if_expression(self, keyword: Token) -> IfExpr:
        condition = self._parse_expression()
        self._expect("{")
        then_expression = self._parse_expression()
        self._expect("}")
        then_block = Block((ExprStmt(then_expression, then_expression.location),), keyword.location)
        else_block = None
        if self._match("else"):
            self._expect("{")
            else_expression = self._parse_expression()
            self._expect("}")
            else_block = Block((ExprStmt(else_expression, else_expression.location),), keyword.location)
        return IfExpr(condition, then_block, else_block, keyword.location)

    def _peek(self) -> Token:
        return self.tokens[self.index]

    def _take(self) -> Token:
        token = self._peek()
        self.index += 1
        return token

    def _at(self, kind: str) -> bool:
        return self._peek().kind == kind

    def _match(self, kind: str) -> bool:
        if not self._at(kind):
            return False
        self._take()
        return True

    def _expect(self, kind: str) -> Token:
        if not self._at(kind):
            self._error(f"expected '{kind}', found '{self._peek().text or 'end of file'}'")
        return self._take()

    def _error(self, message: str, token: Token | None = None):
        at = token or self._peek()
        raise ToyError(f"{at.location}: {message}")


def parse(source: str, path: str = "<memory>", require_main: bool = True) -> Program:
    return Parser(Lexer(source, path).lex(), require_main).parse_program()


def load_program(source: str, path: str) -> Program:
    prelude_path = Path(__file__).resolve().parents[1] / "lib" / "prelude.toy"
    prelude = parse(
        prelude_path.read_text(encoding="utf-8"),
        str(prelude_path),
        require_main=False,
    )
    user = parse(source, path)
    functions = prelude.functions + user.functions
    names = [function.name for function in functions]
    if len(names) != len(set(names)):
        raise ToyError(f"{path}: duplicate function conflicts with the Toy prelude")
    return lower_early_returns(lower_loop_control(Program(functions)))


# ---------------------------------------------------------------------------
# Early-return lowering.
#
# The frontend emits structured control flow (scf.if/scf.while/scf.for), whose
# regions may not contain `func.return`.  Functions that return early from
# inside a loop or conditional are rewritten here:
#   * a hidden mutable flag tracks whether a return has been taken,
#   * nested returns become assignments to a hidden result slot + the flag,
#   * statements following a potential return point are wrapped in
#     `if !flag { ... }`,
#   * `for` loops whose bodies contain returns are lowered to `while` loops so
#     that the loop stops once the flag is set,
#   * the flag is folded into the condition of any loop that may return.
# ---------------------------------------------------------------------------


def _collect_names(program: Program) -> set[str]:
    names: set[str] = set()

    def block_names(block: Block) -> None:
        for statement in block.statements:
            if isinstance(statement, VariableStmt):
                names.add(statement.name)
            elif isinstance(statement, IfStmt):
                block_names(statement.then_block)
                if statement.else_block is not None:
                    block_names(statement.else_block)
            elif isinstance(statement, WhileStmt):
                block_names(statement.body)
            elif isinstance(statement, ForStmt):
                names.add(statement.name)
                block_names(statement.body)

    for function in program.functions:
        names.add(function.name)
        for parameter in function.parameters:
            names.add(parameter.name)
        block_names(function.body)
    return names


def _unique_name(base: str, used: set[str]) -> str:
    name = base
    counter = 0
    while name in used:
        counter += 1
        name = f"{base}_{counter}"
    used.add(name)
    return name


def _is_negative_step(step: Expr | None) -> bool:
    """Whether a for-loop step expression is a negative constant (-1, -2, ...)."""
    if isinstance(step, IntegerExpr):
        return step.value < 0
    return (
        isinstance(step, UnaryExpr)
        and step.operator == "-"
        and isinstance(step.operand, IntegerExpr)
        and step.operand.value > 0
    )


def _for_counter_parts(
    statement: ForStmt, counter_name: str, end_name: str, step_name: str
) -> tuple[VariableStmt, VariableStmt, VariableStmt, BinaryExpr]:
    """Build the counter/end/step declarations and loop condition for a
    for-loop rewritten as a while-loop."""
    location = statement.location
    begin = VariableStmt(True, counter_name, None, statement.begin, location)
    end = VariableStmt(False, end_name, None, statement.end, location)
    step_expression = statement.step if statement.step is not None else IntegerExpr(1, location)
    step = VariableStmt(False, step_name, None, step_expression, location)
    if _is_negative_step(statement.step):
        comparison_op = ">=" if statement.inclusive else ">"
    else:
        comparison_op = "<=" if statement.inclusive else "<"
    comparison = BinaryExpr(
        comparison_op,
        NameExpr(counter_name, location),
        NameExpr(end_name, location),
        location,
    )
    return begin, end, step, comparison


def _block_has_return(statements: tuple[Stmt, ...]) -> bool:
    for statement in statements:
        if isinstance(statement, ReturnStmt):
            return True
        if _stmt_has_return(statement):
            return True
    return False


def _stmt_has_return(statement: Stmt) -> bool:
    if isinstance(statement, IfStmt):
        return _block_has_return(statement.then_block.statements) or (
            statement.else_block is not None
            and _block_has_return(statement.else_block.statements)
        )
    if isinstance(statement, WhileStmt):
        return _block_has_return(statement.body.statements)
    if isinstance(statement, ForStmt):
        return _block_has_return(statement.body.statements)
    return False


def _rewrite_expr(expression: Expr, loop_name: str, counter_name: str, skip: set[str]) -> Expr:
    if isinstance(expression, NameExpr):
        if expression.name == loop_name and loop_name not in skip:
            return NameExpr(counter_name, expression.location)
        return expression
    if isinstance(expression, UnaryExpr):
        return UnaryExpr(
            expression.operator,
            _rewrite_expr(expression.operand, loop_name, counter_name, skip),
            expression.location,
        )
    if isinstance(expression, BinaryExpr):
        return BinaryExpr(
            expression.operator,
            _rewrite_expr(expression.left, loop_name, counter_name, skip),
            _rewrite_expr(expression.right, loop_name, counter_name, skip),
            expression.location,
        )
    if isinstance(expression, AssignExpr):
        return AssignExpr(
            expression.operator,
            _rewrite_expr(expression.target, loop_name, counter_name, skip),
            _rewrite_expr(expression.value, loop_name, counter_name, skip),
            expression.location,
        )
    if isinstance(expression, CallExpr):
        return CallExpr(
            expression.callee,
            tuple(_rewrite_expr(argument, loop_name, counter_name, skip) for argument in expression.arguments),
            expression.location,
        )
    if isinstance(expression, IndexExpr):
        return IndexExpr(
            _rewrite_expr(expression.value, loop_name, counter_name, skip),
            _rewrite_expr(expression.index, loop_name, counter_name, skip),
            expression.location,
        )
    return expression


def _rewrite_block(block: Block, loop_name: str, counter_name: str, skip: set[str]) -> Block:
    current_skip = skip
    statements: list[Stmt] = []
    for statement in block.statements:
        rewritten, current_skip = _rewrite_stmt(statement, loop_name, counter_name, current_skip)
        statements.append(rewritten)
    return Block(tuple(statements), block.location)


def _rewrite_stmt(
    statement: Stmt, loop_name: str, counter_name: str, skip: set[str]
) -> tuple[Stmt, set[str]]:
    if isinstance(statement, VariableStmt):
        initializer = _rewrite_expr(statement.initializer, loop_name, counter_name, skip)
        new_skip = skip | ({statement.name} if statement.name == loop_name else set())
        return VariableStmt(statement.mutable, statement.name, statement.type, initializer, statement.location), new_skip
    if isinstance(statement, ExprStmt):
        return ExprStmt(_rewrite_expr(statement.expression, loop_name, counter_name, skip), statement.location), skip
    if isinstance(statement, IfStmt):
        condition = _rewrite_expr(statement.condition, loop_name, counter_name, skip)
        then_block = _rewrite_block(statement.then_block, loop_name, counter_name, skip)
        else_block = (
            _rewrite_block(statement.else_block, loop_name, counter_name, skip)
            if statement.else_block is not None
            else None
        )
        return IfStmt(condition, then_block, else_block, statement.location), skip
    if isinstance(statement, WhileStmt):
        condition = _rewrite_expr(statement.condition, loop_name, counter_name, skip)
        body = _rewrite_block(statement.body, loop_name, counter_name, skip)
        return WhileStmt(condition, body, statement.location), skip
    if isinstance(statement, ForStmt):
        begin = _rewrite_expr(statement.begin, loop_name, counter_name, skip)
        end = _rewrite_expr(statement.end, loop_name, counter_name, skip)
        step = (
            _rewrite_expr(statement.step, loop_name, counter_name, skip)
            if statement.step is not None
            else None
        )
        inner_skip = skip | {statement.name}
        body = _rewrite_block(statement.body, loop_name, counter_name, inner_skip)
        return ForStmt(statement.name, begin, end, step, statement.inclusive, body, statement.location), skip
    if isinstance(statement, ReturnStmt):
        value = (
            _rewrite_expr(statement.value, loop_name, counter_name, skip)
            if statement.value is not None
            else None
        )
        return ReturnStmt(value, statement.location), skip
    if isinstance(statement, BreakStmt):
        return statement, skip
    if isinstance(statement, ContinueStmt):
        return statement, skip
    raise AssertionError(f"unhandled statement: {statement!r}")


class _EarlyReturnLowering:
    def __init__(self, flag_name: str, value_name: str, counter_name: str) -> None:
        self.flag = flag_name
        self.value = value_name
        self.counter = counter_name
        self.counter_index = 0

    def guard(self, location: Location, body: list[Stmt]) -> IfStmt:
        condition = UnaryExpr("!", NameExpr(self.flag, location), location)
        return IfStmt(condition, Block(tuple(body), location), None, location)

    def flag_off(self, location: Location) -> Expr:
        return UnaryExpr("!", NameExpr(self.flag, location), location)

    def lower_block(
        self, statements: tuple[Stmt, ...], return_type: TypeRef | None, nested: bool = False
    ) -> list[Stmt]:
        result: list[Stmt] = []
        index = 0
        while index < len(statements):
            statement = statements[index]
            lowered, triggers = self.lower_statement(statement, return_type, nested)
            result.extend(lowered)
            index += 1
            if triggers:
                rest = self.lower_block(statements[index:], return_type, True)
                if rest:
                    result.append(self.guard(statement.location, rest))
                break
        return result

    def lower_statement(
        self, statement: Stmt, return_type: TypeRef | None, nested: bool
    ) -> tuple[list[Stmt], bool]:
        if isinstance(statement, ReturnStmt):
            if not nested:
                return [statement], False
            location = statement.location
            lowered: list[Stmt] = []
            if statement.value is not None:
                lowered.append(
                    ExprStmt(
                        AssignExpr("=", NameExpr(self.value, location), statement.value, location),
                        location,
                    )
                )
            lowered.append(
                ExprStmt(
                    AssignExpr("=", NameExpr(self.flag, location), BooleanExpr(True, location), location),
                    location,
                )
            )
            return lowered, True
        if isinstance(statement, IfStmt):
            triggers = _stmt_has_return(statement)
            then_block = Block(
                tuple(self.lower_block(statement.then_block.statements, return_type, nested=True)),
                statement.then_block.location,
            )
            else_block = None
            if statement.else_block is not None:
                else_block = Block(
                    tuple(self.lower_block(statement.else_block.statements, return_type, nested=True)),
                    statement.else_block.location,
                )
            return [IfStmt(statement.condition, then_block, else_block, statement.location)], triggers
        if isinstance(statement, WhileStmt):
            triggers = _stmt_has_return(statement)
            if not triggers:
                return [statement], False
            body = Block(
                tuple(self.lower_block(statement.body.statements, return_type, nested=True)),
                statement.body.location,
            )
            condition = BinaryExpr(
                "&&", self.flag_off(statement.location), statement.condition, statement.location
            )
            return [WhileStmt(condition, body, statement.location)], True
        if isinstance(statement, ForStmt):
            triggers = _stmt_has_return(statement)
            if not triggers:
                return [statement], False
            return self.lower_for(statement, return_type), True
        return [statement], False

    def lower_for(self, statement: ForStmt, return_type: TypeRef | None) -> list[Stmt]:
        location = statement.location
        self.counter_index += 1
        begin, end, step, comparison = _for_counter_parts(
            statement,
            f"{self.counter}_{self.counter_index}",
            f"{self.counter}_end_{self.counter_index}",
            f"{self.counter}_step_{self.counter_index}",
        )
        counter_name = begin.name
        step_name = step.name
        condition = BinaryExpr("&&", self.flag_off(location), comparison, location)
        body_block = _rewrite_block(statement.body, statement.name, counter_name, set())
        body_statements = list(body_block.statements)
        body_statements.append(ExprStmt(AssignExpr("+=", NameExpr(counter_name, location), NameExpr(step_name, location), location), location))
        body = Block(tuple(self.lower_block(tuple(body_statements), return_type, nested=True)), statement.body.location)
        return [begin, end, step, WhileStmt(condition, body, location)]


def _lower_function(function: Function, flag_name: str, value_name: str, counter_name: str) -> Function:
    location = function.location
    prefix: list[Stmt] = [
        VariableStmt(True, flag_name, TypeRef("bool", (), location), BooleanExpr(False, location), location)
    ]
    if function.return_type is not None:
        source = function.return_type.name
        if source == "bool":
            zero: Expr = BooleanExpr(False, location)
        elif source == "f64":
            zero = CallExpr(NameExpr("f64", location), (IntegerExpr(0, location),), location)
        elif source in {"i8", "i16", "i32", "i128"}:
            zero = CallExpr(NameExpr(source, location), (IntegerExpr(0, location),), location)
        elif source == "i64":
            zero = IntegerExpr(0, location)
        else:
            raise ToyError(f"{location}: early return is only supported for scalar return types")
        prefix.append(
            VariableStmt(True, value_name, TypeRef(source, (), location), zero, location)
        )
    lowering = _EarlyReturnLowering(flag_name, value_name, counter_name)
    body = lowering.lower_block(function.body.statements, function.return_type)
    if function.return_type is not None and (not body or not isinstance(body[-1], ReturnStmt)):
        body.append(ReturnStmt(NameExpr(value_name, location), location))
    new_body = Block(tuple(prefix + body), function.body.location)
    return Function(function.name, function.parameters, function.return_type, new_body, function.location)


def lower_early_returns(program: Program) -> Program:
    used = _collect_names(program)
    flag_name = _unique_name("__ret_flag", used)
    value_name = _unique_name("__ret_value", used)
    counter_name = _unique_name("__ret_counter", used)
    functions = []
    for function in program.functions:
        needs = any(_stmt_has_return(statement) for statement in function.body.statements)
        if needs:
            functions.append(_lower_function(function, flag_name, value_name, counter_name))
        else:
            functions.append(function)
    return Program(tuple(functions))


# ---------------------------------------------------------------------------
# break / continue lowering.
#
# `break` and `continue` cannot be represented directly inside scf.while /
# scf.for regions.  Each loop whose body contains one of them is rewritten:
#   * two hidden mutable flags track whether a break/continue was taken,
#   * the flags are reset at the top of every iteration,
#   * statements following a break/continue point are guarded by
#     `if !(flag_break || flag_continue) { ... }`,
#   * the loop condition gains `&& !flag_break`,
#   * `for` loops with break/continue become `while` loops over a counter,
#     so the loop really stops instead of burning remaining iterations.
# Nested loops get their own flags; a break inside an inner loop never
# disturbs the outer one.
# ---------------------------------------------------------------------------


def _stmt_has_loop_control(statement: Stmt) -> bool:
    if isinstance(statement, (BreakStmt, ContinueStmt)):
        return True
    if isinstance(statement, IfStmt):
        return _block_has_loop_control(statement.then_block.statements) or (
            statement.else_block is not None
            and _block_has_loop_control(statement.else_block.statements)
        )
    if isinstance(statement, WhileStmt):
        return _block_has_loop_control(statement.body.statements)
    if isinstance(statement, ForStmt):
        return _block_has_loop_control(statement.body.statements)
    return False


def _block_has_loop_control(statements: tuple[Stmt, ...]) -> bool:
    return any(_stmt_has_loop_control(statement) for statement in statements)


class _LoopControlLowering:
    def __init__(self, break_base: str, continue_base: str, counter_base: str) -> None:
        self.break_base = break_base
        self.continue_base = continue_base
        self.counter_base = counter_base
        self.loop_index = 0

    def lower_program(self, program: Program) -> Program:
        functions = []
        for function in program.functions:
            body = Block(
                tuple(self.lower_statements(function.body.statements, in_loop=False)),
                function.body.location,
            )
            functions.append(Function(function.name, function.parameters, function.return_type, body, function.location))
        return Program(tuple(functions))

    def fresh_names(self) -> tuple[str, str]:
        self.loop_index += 1
        return f"{self.break_base}_{self.loop_index}", f"{self.continue_base}_{self.loop_index}"

    def lower_statements(self, statements: tuple[Stmt, ...], in_loop: bool) -> list[Stmt]:
        result: list[Stmt] = []
        for statement in statements:
            if isinstance(statement, IfStmt):
                then_statements = self.lower_statements(statement.then_block.statements, in_loop)
                then_block = Block(tuple(then_statements), statement.then_block.location)
                else_block = None
                if statement.else_block is not None:
                    else_statements = self.lower_statements(statement.else_block.statements, in_loop)
                    else_block = Block(tuple(else_statements), statement.else_block.location)
                result.append(IfStmt(statement.condition, then_block, else_block, statement.location))
                continue
            if isinstance(statement, WhileStmt):
                body_statements = self.lower_statements(statement.body.statements, in_loop=True)
                if _block_has_loop_control(tuple(body_statements)):
                    break_name, continue_name = self.fresh_names()
                    result.extend(self.transform_while(statement, tuple(body_statements), break_name, continue_name))
                else:
                    result.append(
                        WhileStmt(statement.condition, Block(tuple(body_statements), statement.body.location), statement.location)
                    )
                continue
            if isinstance(statement, ForStmt):
                body_statements = self.lower_statements(statement.body.statements, in_loop=True)
                if _block_has_loop_control(tuple(body_statements)):
                    break_name, continue_name = self.fresh_names()
                    result.extend(self.transform_for(statement, tuple(body_statements), break_name, continue_name))
                else:
                    result.append(
                        ForStmt(statement.name, statement.begin, statement.end, statement.step, statement.inclusive, Block(tuple(body_statements), statement.body.location), statement.location)
                    )
                continue
            if isinstance(statement, (BreakStmt, ContinueStmt)):
                if not in_loop:
                    raise ToyError(f"{statement.location}: 'break'/'continue' outside of a loop")
                result.append(statement)
                continue
            result.append(statement)
        return result

    def flag_declarations(self, location: Location, break_name: str, continue_name: str) -> list[Stmt]:
        return [
            VariableStmt(True, break_name, TypeRef("bool", (), location), BooleanExpr(False, location), location),
            VariableStmt(True, continue_name, TypeRef("bool", (), location), BooleanExpr(False, location), location),
        ]

    def flag_resets(self, location: Location, break_name: str, continue_name: str) -> list[Stmt]:
        return [
            ExprStmt(AssignExpr("=", NameExpr(break_name, location), BooleanExpr(False, location), location), location),
            ExprStmt(AssignExpr("=", NameExpr(continue_name, location), BooleanExpr(False, location), location), location),
        ]

    def segment(self, statements: tuple[Stmt, ...], break_name: str, continue_name: str) -> list[Stmt]:
        result: list[Stmt] = []
        index = 0
        while index < len(statements):
            statement = statements[index]
            lowered, triggers = self.segment_statement(statement, break_name, continue_name)
            result.extend(lowered)
            index += 1
            if triggers:
                rest = self.segment(statements[index:], break_name, continue_name)
                if rest:
                    location = statement.location
                    condition = UnaryExpr(
                        "!",
                        BinaryExpr("||", NameExpr(break_name, location), NameExpr(continue_name, location), location),
                        location,
                    )
                    result.append(IfStmt(condition, Block(tuple(rest), location), None, location))
                break
        return result

    def segment_statement(self, statement: Stmt, break_name: str, continue_name: str) -> tuple[list[Stmt], bool]:
        if isinstance(statement, BreakStmt):
            location = statement.location
            return [ExprStmt(AssignExpr("=", NameExpr(break_name, location), BooleanExpr(True, location), location), location)], True
        if isinstance(statement, ContinueStmt):
            location = statement.location
            return [ExprStmt(AssignExpr("=", NameExpr(continue_name, location), BooleanExpr(True, location), location), location)], True
        if isinstance(statement, IfStmt):
            triggers = _stmt_has_loop_control(statement)
            then_block = Block(tuple(self.segment(statement.then_block.statements, break_name, continue_name)), statement.then_block.location)
            else_block = None
            if statement.else_block is not None:
                else_block = Block(tuple(self.segment(statement.else_block.statements, break_name, continue_name)), statement.else_block.location)
            return [IfStmt(statement.condition, then_block, else_block, statement.location)], triggers
        return [statement], False

    def transform_while(self, statement: WhileStmt, body_statements: tuple[Stmt, ...], break_name: str, continue_name: str) -> list[Stmt]:
        location = statement.location
        body = Block(
            tuple(self.flag_resets(location, break_name, continue_name) + self.segment(body_statements, break_name, continue_name)),
            statement.body.location,
        )
        condition = BinaryExpr(
            "&&", UnaryExpr("!", NameExpr(break_name, location), location), statement.condition, location
        )
        return self.flag_declarations(location, break_name, continue_name) + [WhileStmt(condition, body, location)]

    def transform_for(self, statement: ForStmt, body_statements: tuple[Stmt, ...], break_name: str, continue_name: str) -> list[Stmt]:
        location = statement.location
        counter_name = f"{self.counter_base}_{self.loop_index}"
        step_name = f"{self.counter_base}_step_{self.loop_index}"
        begin, end, step, comparison = _for_counter_parts(
            statement,
            counter_name,
            f"{self.counter_base}_end_{self.loop_index}",
            step_name,
        )
        condition = BinaryExpr(
            "&&", UnaryExpr("!", NameExpr(break_name, location), location), comparison, location
        )
        body_block = _rewrite_block(statement.body, statement.name, counter_name, set())
        processed = self.lower_statements(body_block.statements, in_loop=True)
        segmented = self.segment(tuple(processed), break_name, continue_name)
        increment = ExprStmt(
            AssignExpr("+=", NameExpr(counter_name, location), NameExpr(step_name, location), location),
            location,
        )
        increment_guard = IfStmt(
            UnaryExpr("!", NameExpr(break_name, location), location),
            Block((increment,), location),
            None,
            location,
        )
        body = Block(tuple(self.flag_resets(location, break_name, continue_name) + segmented + [increment_guard]), statement.body.location)
        return self.flag_declarations(location, break_name, continue_name) + [begin, end, step, WhileStmt(condition, body, location)]


def lower_loop_control(program: Program) -> Program:
    used = _collect_names(program)
    break_name = _unique_name("__break", used)
    continue_name = _unique_name("__continue", used)
    counter_name = _unique_name("__loop_counter", used)
    return _LoopControlLowering(break_name, continue_name, counter_name).lower_program(program)


SCALAR_TYPES = {
    "bool": "i1",
    "i8": "i8",
    "i16": "i16",
    "i32": "i32",
    "i64": "i64",
    "i128": "i128",
    "f64": "f64",
    "heap": "!llvm.ptr",
    "map": "!llvm.ptr",
    "ordered": "!llvm.ptr",
    "string": "!llvm.ptr",
}


class MlirGenerator:
    def __init__(self, program: Program) -> None:
        self.program = program
        self.lines: list[str] = []
        self.indent = 0
        self.next_value = 0
        self.scopes: list[dict[str, Binding]] = []
        self.functions = {function.name: function for function in program.functions}
        self.current_function: Function | None = None
        self.saw_terminator = False
        self.statement_value: Value | None = None

    def generate(self) -> str:
        self._emit("module {")
        self.indent += 1
        for function in self.program.functions:
            self._generate_function(function)
        self.indent -= 1
        self._emit("}")
        return "\n".join(self.lines) + "\n"

    def _generate_function(self, function: Function) -> None:
        self.current_function = function
        self.scopes = [{}]
        self.saw_terminator = False
        arguments = []
        for parameter in function.parameters:
            mlir_type = self._type(parameter.type)
            value = self._new_value(parameter.name)
            arguments.append(f"{value.name}: {mlir_type}")
            self._bind(parameter.name, Binding(Value(value.name, mlir_type), False), parameter.location)
        source_return = self._type(function.return_type) if function.return_type else None
        mlir_return = "i32" if function.name == "main" and source_return is None else source_return
        signature = f"func.func @{function.name}({', '.join(arguments)})"
        if mlir_return is not None:
            signature += f" -> {mlir_return}"
        self._emit(signature + " {")
        self.indent += 1
        self._generate_statements(function.body.statements, create_scope=False)
        if not self.saw_terminator:
            if function.name == "main" and source_return is None:
                zero = self._constant(0, "i32")
                self._emit(f"func.return {zero.name} : i32")
            elif source_return is None:
                self._emit("func.return")
            else:
                raise ToyError(f"{function.location}: function '{function.name}' may not return a value")
        self.indent -= 1
        self._emit("}")

    def _generate_statements(self, statements: tuple[Stmt, ...], create_scope: bool = True) -> Value | None:
        if create_scope:
            self.scopes.append({})
        last_value: Value | None = None
        for statement in statements:
            if self.saw_terminator:
                raise ToyError(f"{statement.location}: unreachable statement")
            self.statement_value = None
            self._generate_statement(statement)
            if isinstance(statement, ExprStmt):
                last_value = self.statement_value
        if create_scope:
            self.scopes.pop()
        return last_value

    def _generate_statement(self, statement: Stmt) -> None:
        if isinstance(statement, VariableStmt):
            initializer = self._generate_expression(statement.initializer)
            if statement.type is not None:
                expected = self._type(statement.type)
                self._require_type(initializer, expected, statement.location)
            if statement.mutable:
                slot = self._new_value(f"{statement.name}_slot")
                self._emit(f"{slot.name} = memref.alloca() : memref<{initializer.type}>")
                self._emit(f"memref.store {initializer.name}, {slot.name}[] : memref<{initializer.type}>")
                self._bind(statement.name, Binding(Value(slot.name, initializer.type), True), statement.location)
            else:
                self._bind(statement.name, Binding(initializer, False), statement.location)
            return
        if isinstance(statement, ExprStmt):
            self.statement_value = self._generate_expression(statement.expression)
            return
        if isinstance(statement, IfStmt):
            condition = self._generate_expression(statement.condition)
            self._require_type(condition, "i1", statement.condition.location)
            self._emit(f"scf.if {condition.name} {{")
            self.indent += 1
            self._generate_statements(statement.then_block.statements)
            then_terminated = self.saw_terminator
            self.saw_terminator = False
            self.indent -= 1
            if statement.else_block is None:
                self._emit("}")
            else:
                self._emit("} else {")
                self.indent += 1
                self._generate_statements(statement.else_block.statements)
                else_terminated = self.saw_terminator
                self.saw_terminator = then_terminated and else_terminated
                self.indent -= 1
                self._emit("}")
            return
        if isinstance(statement, WhileStmt):
            self._emit("scf.while : () -> () {")
            self.indent += 1
            condition = self._generate_expression(statement.condition)
            self._require_type(condition, "i1", statement.condition.location)
            self._emit(f"scf.condition({condition.name})")
            self.indent -= 1
            self._emit("} do {")
            self.indent += 1
            self._generate_statements(statement.body.statements)
            if self.saw_terminator:
                raise ToyError(f"{statement.location}: return inside while is not supported yet")
            self._emit("scf.yield")
            self.indent -= 1
            self._emit("}")
            return
        if isinstance(statement, ForStmt):
            begin = self._generate_expression(statement.begin)
            end = self._generate_expression(statement.end)
            self._require_type(end, begin.type, statement.location)
            self._require_integer(begin, statement.location)
            step = (
                self._generate_expression(statement.step)
                if statement.step is not None
                else self._constant(1, begin.type)
            )
            self._require_type(step, begin.type, statement.location)
            if _is_negative_step(statement.step):
                self._generate_descending_for(statement, begin, end, step)
                return
            if statement.inclusive:
                end = self._binary("arith.addi", end, self._constant(1, end.type))
            begin_index = self._index_cast(begin)
            end_index = self._index_cast(end)
            step_index = self._index_cast(step)
            induction = self._new_value(statement.name)
            self._emit(
                f"scf.for {induction.name} = {begin_index.name} to {end_index.name} "
                f"step {step_index.name} {{"
            )
            self.indent += 1
            self.scopes.append({})
            self._bind(statement.name, Binding(Value(induction.name, "index"), False), statement.location)
            self._generate_statements(statement.body.statements, create_scope=False)
            self.scopes.pop()
            if self.saw_terminator:
                raise ToyError(f"{statement.location}: return inside for is not supported yet")
            self._emit("scf.yield")
            self.indent -= 1
            self._emit("}")
            return
        if isinstance(statement, ReturnStmt):
            expected = self._source_return_type()
            if statement.value is None:
                if expected is not None:
                    raise ToyError(f"{statement.location}: return value of type {expected} is required")
                self._emit("func.return")
            else:
                value = self._generate_expression(statement.value)
                if expected is None:
                    raise ToyError(f"{statement.location}: void function cannot return a value")
                self._require_type(value, expected, statement.location)
                self._emit(f"func.return {value.name} : {value.type}")
            self.saw_terminator = True
            return
        if isinstance(statement, BreakStmt):
            raise ToyError(f"{statement.location}: internal error: 'break' reached codegen")
        if isinstance(statement, ContinueStmt):
            raise ToyError(f"{statement.location}: internal error: 'continue' reached codegen")
        raise AssertionError(f"unhandled statement: {statement!r}")

    def _generate_descending_for(self, statement: ForStmt, begin: Value, end: Value, step: Value) -> None:
        # A for loop with a constant negative step cannot use scf.for (which
        # requires a positive step); lower it to a while loop over a counter.
        counter_slot = self._new_value(f"{statement.name}_counter_slot")
        self._emit(f"{counter_slot.name} = memref.alloca() : memref<{begin.type}>")
        self._emit(f"memref.store {begin.name}, {counter_slot.name}[] : memref<{begin.type}>")
        self._emit("scf.while : () -> () {")
        self.indent += 1
        current = self._new_value(f"{statement.name}_counter")
        self._emit(f"{current.name} = memref.load {counter_slot.name}[] : memref<{begin.type}>")
        predicate = "sge" if statement.inclusive else "sgt"
        comparison = self._new_value("condition")
        self._emit(
            f"{comparison.name} = arith.cmpi {predicate}, {current.name}, {end.name} : {begin.type}"
        )
        self._emit(f"scf.condition({comparison.name})")
        self.indent -= 1
        self._emit("} do {")
        self.indent += 1
        induction = self._new_value(statement.name)
        self._emit(f"{induction.name} = memref.load {counter_slot.name}[] : memref<{begin.type}>")
        self.scopes.append({})
        self._bind(statement.name, Binding(Value(induction.name, begin.type), False), statement.location)
        self._generate_statements(statement.body.statements, create_scope=False)
        self.scopes.pop()
        self._emit(f"memref.store {induction.name}, {counter_slot.name}[] : memref<{begin.type}>")
        next_value = self._new_value(f"{statement.name}_next")
        self._emit(
            f"{next_value.name} = arith.addi {induction.name}, {step.name} : {begin.type}"
        )
        self._emit(f"memref.store {next_value.name}, {counter_slot.name}[] : memref<{begin.type}>")
        self._emit("scf.yield")
        self.indent -= 1
        self._emit("}")
        return

    def _generate_expression(self, expression: Expr) -> Value:
        if isinstance(expression, IntegerExpr):
            return self._constant(expression.value, "i64")
        if isinstance(expression, FloatExpr):
            result = self._new_value("f64")
            literal = format(expression.value, ".17g")
            if "." not in literal:
                if "e" in literal:
                    literal = literal.replace("e", ".0e", 1)
                else:
                    literal += ".0"
            self._emit(f"{result.name} = arith.constant {literal} : f64")
            return Value(result.name, "f64")
        if isinstance(expression, BooleanExpr):
            return self._constant(int(expression.value), "i1")
        if isinstance(expression, StringExpr):
            raise ToyError(f"{expression.location}: string values are only supported by print calls yet")
        if isinstance(expression, NameExpr):
            binding = self._lookup(expression.name, expression.location)
            if not binding.mutable:
                if binding.value.type == "index":
                    return self._integer_cast(binding.value, "i64")
                return binding.value
            result = self._new_value(expression.name)
            self._emit(
                f"{result.name} = memref.load {binding.value.name}[] : memref<{binding.value.type}>"
            )
            return Value(result.name, binding.value.type)
        if isinstance(expression, UnaryExpr):
            operand = self._generate_expression(expression.operand)
            if expression.operator == "+":
                if operand.type != "f64":
                    self._require_integer(operand, expression.location)
                return operand
            if expression.operator == "-":
                if operand.type == "f64":
                    result = self._new_value("neg")
                    self._emit(f"{result.name} = arith.negf {operand.name} : f64")
                    return Value(result.name, "f64")
                self._require_integer(operand, expression.location)
                zero = self._constant(0, operand.type)
                return self._binary("arith.subi", zero, operand)
            if expression.operator == "!":
                self._require_type(operand, "i1", expression.location)
                one = self._constant(1, "i1")
                return self._binary("arith.xori", operand, one)
            raise AssertionError(expression.operator)
        if isinstance(expression, BinaryExpr):
            return self._generate_binary(expression)
        if isinstance(expression, AssignExpr):
            return self._generate_assignment(expression)
        if isinstance(expression, CallExpr):
            return self._generate_call(expression)
        if isinstance(expression, IndexExpr):
            array, index, element_type = self._generate_index(expression)
            result = self._new_value("element")
            self._emit(
                f"{result.name} = memref.load {array.name}[{index.name}] : {array.type}"
            )
            return Value(result.name, element_type)
        if isinstance(expression, ArrayLitExpr):
            if not expression.elements:
                raise ToyError(f"{expression.location}: array literal needs at least one element")
            elements = [self._generate_expression(element) for element in expression.elements]
            element_type = elements[0].type
            if element_type not in {"i1", "i8", "i16", "i32", "i64", "i128", "f64"}:
                raise ToyError(f"{expression.location}: array literal elements must be scalar")
            for element in elements[1:]:
                self._require_type(element, element_type, expression.location)
            result = self._new_value("array_literal")
            size = self._constant(len(elements), "index")
            self._emit(f"{result.name} = memref.alloc({size.name}) : memref<?x{element_type}>")
            for position, element in enumerate(elements):
                index = self._constant(position, "index")
                self._emit(
                    f"memref.store {element.name}, {result.name}[{index.name}] : memref<?x{element_type}>"
                )
            return Value(result.name, f"memref<?x{element_type}>")
        if isinstance(expression, IfExpr):
            if expression.else_block is None:
                raise ToyError(f"{expression.location}: an if expression requires an else branch")
            condition = self._generate_expression(expression.condition)
            self._require_type(condition, "i1", expression.condition.location)
            saved_lines = self.lines
            self.indent += 1
            self.lines = []
            then_value = self._generate_statements(expression.then_block.statements, create_scope=True)
            then_lines = self.lines
            self.lines = saved_lines
            self.lines = []
            else_value = self._generate_statements(expression.else_block.statements, create_scope=True)
            else_lines = self.lines
            self.lines = saved_lines
            self.indent -= 1
            if then_value is None or else_value is None:
                raise ToyError(f"{expression.location}: if expression branches must end with an expression")
            self._require_type(else_value, then_value.type, expression.location)
            result = self._new_value("if_expr")
            self._emit(f"{result.name} = scf.if {condition.name} -> ({then_value.type}) {{")
            self.indent += 1
            self.lines.extend(then_lines)
            self._emit(f"scf.yield {then_value.name} : {then_value.type}")
            self.indent -= 1
            self._emit("} else {")
            self.indent += 1
            self.lines.extend(else_lines)
            self._emit(f"scf.yield {else_value.name} : {else_value.type}")
            self.indent -= 1
            self._emit("}")
            return Value(result.name, then_value.type)
        raise AssertionError(f"unhandled expression: {expression!r}")

    def _generate_binary(self, expression: BinaryExpr) -> Value:
        left = self._generate_expression(expression.left)
        if expression.operator in {"&&", "||"}:
            self._require_type(left, "i1", expression.location)
            result = self._new_value("logical")
            self._emit(f"{result.name} = scf.if {left.name} -> (i1) {{")
            self.indent += 1
            if expression.operator == "&&":
                right = self._generate_expression(expression.right)
                self._require_type(right, "i1", expression.location)
                self._emit(f"scf.yield {right.name} : i1")
            else:
                true_value = self._constant(1, "i1")
                self._emit(f"scf.yield {true_value.name} : i1")
            self.indent -= 1
            self._emit("} else {")
            self.indent += 1
            if expression.operator == "&&":
                false_value = self._constant(0, "i1")
                self._emit(f"scf.yield {false_value.name} : i1")
            else:
                right = self._generate_expression(expression.right)
                self._require_type(right, "i1", expression.location)
                self._emit(f"scf.yield {right.name} : i1")
            self.indent -= 1
            self._emit("}")
            return Value(result.name, "i1")

        right = self._generate_expression(expression.right)
        if right.type != left.type and self._is_integer_type(right.type) and self._is_integer_type(left.type):
            right = self._integer_cast(right, left.type)
        self._require_type(right, left.type, expression.location)
        if left.type == "f64":
            float_arithmetic = {
                "+": "arith.addf",
                "-": "arith.subf",
                "*": "arith.mulf",
                "/": "arith.divf",
            }
            if expression.operator in float_arithmetic:
                return self._binary(float_arithmetic[expression.operator], left, right)
            float_predicates = {
                "==": "oeq",
                "!=": "one",
                "<": "olt",
                "<=": "ole",
                ">": "ogt",
                ">=": "oge",
            }
            if expression.operator in float_predicates:
                result = self._new_value("cmp")
                self._emit(
                    f"{result.name} = arith.cmpf {float_predicates[expression.operator]}, "
                    f"{left.name}, {right.name} : f64"
                )
                return Value(result.name, "i1")
            raise ToyError(f"{expression.location}: operator '{expression.operator}' is invalid for f64")
        arithmetic = {
            "+": "arith.addi",
            "-": "arith.subi",
            "*": "arith.muli",
            "/": "arith.divsi",
            "%": "arith.remsi",
            "&": "arith.andi",
            "|": "arith.ori",
            "^": "arith.xori",
            "<<": "arith.shli",
            ">>": "arith.shrsi",
        }
        if expression.operator in arithmetic:
            self._require_integer(left, expression.location)
            if expression.operator in {"<<", ">>"} and right.type != left.type:
                self._require_integer(right, expression.location)
                right = self._integer_cast(right, left.type)
            return self._binary(arithmetic[expression.operator], left, right)
        predicates = {
            "==": "eq",
            "!=": "ne",
            "<": "slt",
            "<=": "sle",
            ">": "sgt",
            ">=": "sge",
        }
        if expression.operator in predicates:
            if right.type != left.type and self._is_integer_type(right.type) and self._is_integer_type(left.type):
                right = self._integer_cast(right, left.type)
            result = self._new_value("cmp")
            self._emit(
                f"{result.name} = arith.cmpi {predicates[expression.operator]}, "
                f"{left.name}, {right.name} : {left.type}"
            )
            return Value(result.name, "i1")
        raise AssertionError(expression.operator)

    def _generate_assignment(self, expression: AssignExpr) -> Value:
        if isinstance(expression.target, IndexExpr):
            array, index, element_type = self._generate_index(expression.target)
            value = self._generate_expression(expression.value)
            if value.type != element_type:
                if self._is_integer_type(value.type) and self._is_integer_type(element_type):
                    value = self._integer_cast(value, element_type)
                elif value.type == "f64" or element_type == "f64":
                    value = self._numeric_cast(value, element_type, expression.location)
                else:
                    self._require_type(value, element_type, expression.location)
            if expression.operator != "=":
                current = self._new_value("element")
                self._emit(
                    f"{current.name} = memref.load {array.name}[{index.name}] : {array.type}"
                )
                operation = self._compound_operation(expression.operator, element_type)
                value = self._binary(operation, Value(current.name, element_type), value)
            self._emit(f"memref.store {value.name}, {array.name}[{index.name}] : {array.type}")
            return value
        if not isinstance(expression.target, NameExpr):
            raise ToyError(f"{expression.location}: assignment target must be a variable")
        binding = self._lookup(expression.target.name, expression.location)
        if not binding.mutable:
            raise ToyError(f"{expression.location}: cannot assign to immutable binding '{expression.target.name}'")
        value = self._generate_expression(expression.value)
        if value.type != binding.value.type:
            if self._is_integer_type(value.type) and self._is_integer_type(binding.value.type):
                value = self._integer_cast(value, binding.value.type)
            elif value.type == "f64" or binding.value.type == "f64":
                value = self._numeric_cast(value, binding.value.type, expression.location)
            else:
                self._require_type(value, binding.value.type, expression.location)
        if expression.operator != "=":
            current = self._new_value(expression.target.name)
            self._emit(
                f"{current.name} = memref.load {binding.value.name}[] : memref<{binding.value.type}>"
            )
            operation = self._compound_operation(expression.operator, binding.value.type)
            value = self._binary(operation, Value(current.name, binding.value.type), value)
        self._emit(f"memref.store {value.name}, {binding.value.name}[] : memref<{binding.value.type}>")
        return value

    def _generate_call(self, expression: CallExpr) -> Value:
        if not isinstance(expression.callee, NameExpr):
            raise ToyError(f"{expression.location}: call target must be a function name")
        name = expression.callee.name
        if name in {"bool", "i8", "i16", "i32", "i64", "i128", "f64"}:
            if len(expression.arguments) != 1:
                raise ToyError(f"{expression.location}: {name}() expects one value")
            value = self._generate_expression(expression.arguments[0])
            return self._numeric_cast(value, SCALAR_TYPES[name], expression.location)
        if name in {"min", "max"}:
            return self._generate_min_max(name, expression)
        if name == "popcount":
            if len(expression.arguments) != 1:
                raise ToyError(f"{expression.location}: popcount() expects one value")
            value = self._generate_expression(expression.arguments[0])
            self._require_integer(value, expression.location)
            if value.type != "i64":
                value = self._integer_cast(value, "i64")
            result = self._new_value("popcount")
            self._emit(f'{result.name} = "toy.popcount"({value.name}) : (i64) -> i64')
            return Value(result.name, "i64")
        if name == "flush":
            if expression.arguments:
                raise ToyError(f"{expression.location}: flush() takes no arguments")
            self._emit('"toy.flush"() : () -> ()')
            return Value("", "none")
        if name == "swap":
            if len(expression.arguments) != 2:
                raise ToyError(f"{expression.location}: swap() expects two variables or elements")
            loaded: list[tuple[Value, str]] = []
            for target in expression.arguments:
                if isinstance(target, NameExpr):
                    binding = self._lookup(target.name, target.location)
                    if not binding.mutable:
                        raise ToyError(f"{expression.location}: cannot swap immutable binding '{target.name}'")
                    value = self._new_value("swap")
                    self._emit(
                        f"{value.name} = memref.load {binding.value.name}[] : memref<{binding.value.type}>"
                    )
                    loaded.append((Value(value.name, binding.value.type), ""))
                elif isinstance(target, IndexExpr):
                    array, index, element_type = self._generate_index(target)
                    value = self._new_value("swap")
                    self._emit(
                        f"{value.name} = memref.load {array.name}[{index.name}] : {array.type}"
                    )
                    loaded.append((Value(value.name, element_type), ""))
                else:
                    raise ToyError(f"{expression.location}: swap() arguments must be variables or elements")
            first, second = loaded
            if second[0].type != first[0].type and self._is_integer_type(second[0].type) and self._is_integer_type(first[0].type):
                second = (self._integer_cast(second[0], first[0].type), second[1])
            self._require_type(second[0], first[0].type, expression.location)
            for target, value in zip(expression.arguments, (second[0], first[0]), strict=True):
                if isinstance(target, NameExpr):
                    binding = self._lookup(target.name, target.location)
                    self._emit(f"memref.store {value.name}, {binding.value.name}[] : memref<{binding.value.type}>")
                else:
                    array, index, element_type = self._generate_index(target)
                    self._emit(f"memref.store {value.name}, {array.name}[{index.name}] : {array.type}")
            return Value("", "none")
        if name in {"cos", "sin", "sqrt", "log", "exp", "floor", "ceil", "tan"}:
            if len(expression.arguments) != 1:
                raise ToyError(f"{expression.location}: {name}() expects one f64 value")
            value = self._generate_expression(expression.arguments[0])
            self._require_type(value, "f64", expression.location)
            result = self._new_value(name)
            self._emit(f"{result.name} = math.{name} {value.name} : f64")
            return Value(result.name, "f64")
        if name in {"print", "println"}:
            for argument in expression.arguments:
                if isinstance(argument, StringExpr):
                    self._emit_text(argument.value)
                else:
                    value = self._generate_expression(argument)
                    self._require_integer(value, expression.location)
                    if value.type in {"i1", "i8", "i16", "i32"}:
                        value = self._integer_cast(value, "i64")
                    if value.type == "i128":
                        self._emit(f'"toy.print_i128"({value.name}) {{newline = false}} : (i128) -> ()')
                    else:
                        self._emit(f'"toy.print"({value.name}) {{newline = false}} : ({value.type}) -> ()')
            if name == "println":
                self._emit_character("\n")
            return Value("", "none")
        if name == "print_fixed":
            if len(expression.arguments) != 2:
                raise ToyError(f"{expression.location}: print_fixed() expects a value and precision")
            value = self._generate_expression(expression.arguments[0])
            precision = self._generate_expression(expression.arguments[1])
            self._require_type(value, "f64", expression.location)
            self._require_type(precision, "i64", expression.location)
            self._emit(
                f'"toy.print_f64"({value.name}, {precision.name}) : (f64, i64) -> ()'
            )
            return Value("", "none")

        arguments = [self._generate_expression(argument) for argument in expression.arguments]
        if name == "read":
            if arguments:
                raise ToyError(f"{expression.location}: read() takes no arguments")
            result = self._new_value("read")
            self._emit(f'{result.name} = "toy.read"() : () -> i64')
            return Value(result.name, "i64")
        if name == "array":
            if len(arguments) != 2:
                raise ToyError(f"{expression.location}: array() expects a size and initial value")
            size, initial = arguments
            self._require_type(size, "i64", expression.location)
            if initial.type not in {"i1", "i8", "i16", "i32", "i64", "i128", "f64"}:
                raise ToyError(f"{expression.location}: array initial value must be scalar")
            memref_type = f"memref<?x{initial.type}>"
            dynamic_size = self._index_cast(size)
            result = self._new_value("array")
            self._emit(f"{result.name} = memref.alloc({dynamic_size.name}) : {memref_type}")
            zero = self._constant(0, "index")
            one = self._constant(1, "index")
            size_index = self._index_cast(size)
            induction = self._new_value("initialize")
            self._emit(
                f"scf.for {induction.name} = {zero.name} to {size_index.name} step {one.name} {{"
            )
            self.indent += 1
            self._emit(
                f"memref.store {initial.name}, {result.name}[{induction.name}] : {memref_type}"
            )
            self._emit("scf.yield")
            self.indent -= 1
            self._emit("}")
            return Value(result.name, memref_type)
        if name == "map":
            if len(arguments) != 1 or arguments[0].type != "i64":
                raise ToyError(f"{expression.location}: map() expects one i64 capacity hint")
            result = self._new_value("map")
            self._emit(
                f'{result.name} = "toy.map_create"({arguments[0].name}) : (i64) -> !llvm.ptr'
            )
            return Value(result.name, "!llvm.ptr")
        if name == "map_get":
            if len(arguments) != 3 or arguments[1].type != "i64" or arguments[2].type != "i64":
                raise ToyError(f"{expression.location}: map_get() expects a map, key, and default")
            handle = self._handle_value(arguments[0], expression.location)
            result = self._new_value("map_value")
            self._emit(
                f'{result.name} = "toy.map_get"({handle.name}, {arguments[1].name}, '
                f'{arguments[2].name}) : (!llvm.ptr, i64, i64) -> i64'
            )
            return Value(result.name, "i64")
        if name == "map_set":
            if len(arguments) != 3 or arguments[1].type != "i64" or arguments[2].type != "i64":
                raise ToyError(f"{expression.location}: map_set() expects a map, key, and value")
            handle = self._handle_value(arguments[0], expression.location)
            self._emit(
                f'"toy.map_set"({handle.name}, {arguments[1].name}, {arguments[2].name}) '
                ': (!llvm.ptr, i64, i64) -> ()'
            )
            return Value("", "none")
        if name == "ordered":
            if len(arguments) != 1 or arguments[0].type != "i64":
                raise ToyError(f"{expression.location}: ordered() expects one capacity hint")
            result = self._new_value("ordered")
            self._emit(
                f'{result.name} = "toy.ordered_create"({arguments[0].name}) : (i64) -> !llvm.ptr'
            )
            return Value(result.name, "!llvm.ptr")
        if name in {"ordered_insert", "ordered_erase"}:
            if len(arguments) != 2 or arguments[1].type != "i64":
                raise ToyError(f"{expression.location}: {name}() expects an ordered set and key")
            handle = self._handle_value(arguments[0], expression.location)
            operation = "ordered_insert" if name == "ordered_insert" else "ordered_erase"
            self._emit(
                f'"toy.{operation}"({handle.name}, {arguments[1].name}) '
                ': (!llvm.ptr, i64) -> ()'
            )
            return Value("", "none")
        ordered_modes = {
            "ordered_ceiling": 0,
            "ordered_higher": 1,
            "ordered_floor": 2,
            "ordered_first": 3,
            "ordered_last": 4,
            "ordered_size": 5,
        }
        if name in ordered_modes:
            unary = name in {"ordered_first", "ordered_last", "ordered_size"}
            expected_count = 1 if unary else 3
            if len(arguments) != expected_count:
                raise ToyError(
                    f"{expression.location}: {name}() expects "
                    + ("an ordered set" if unary else "an ordered set, key, and default")
                )
            handle = self._handle_value(arguments[0], expression.location)
            key = self._constant(0, "i64") if unary else arguments[1]
            default = self._constant(0, "i64") if unary else arguments[2]
            if key.type != "i64" or default.type != "i64":
                raise ToyError(f"{expression.location}: ordered query values must be i64")
            mode = self._constant(ordered_modes[name], "i64")
            result = self._new_value("ordered_value")
            self._emit(
                f'{result.name} = "toy.ordered_query"({handle.name}, {key.name}, '
                f'{mode.name}, {default.name}) : (!llvm.ptr, i64, i64, i64) -> i64'
            )
            return Value(result.name, "i64")
        if name == "heap":
            if len(arguments) != 1 or arguments[0].type != "i64":
                raise ToyError(f"{expression.location}: heap() expects one capacity hint")
            result = self._new_value("heap")
            self._emit(
                f'{result.name} = "toy.heap_create"({arguments[0].name}) : (i64) -> !llvm.ptr'
            )
            return Value(result.name, "!llvm.ptr")
        if name == "heap_push":
            if len(arguments) != 3 or arguments[1].type != "i64" or arguments[2].type != "i64":
                raise ToyError(f"{expression.location}: heap_push() expects a heap and two i64 values")
            handle = self._handle_value(arguments[0], expression.location)
            self._emit(
                f'"toy.heap_push"({handle.name}, {arguments[1].name}, {arguments[2].name}) '
                ': (!llvm.ptr, i64, i64) -> ()'
            )
            return Value("", "none")
        if name == "heap_pop":
            if len(arguments) != 1:
                raise ToyError(f"{expression.location}: heap_pop() expects one heap")
            handle = self._handle_value(arguments[0], expression.location)
            self._emit(f'"toy.heap_pop"({handle.name}) : (!llvm.ptr) -> ()')
            return Value("", "none")
        heap_modes = {"heap_first": 0, "heap_second": 1, "heap_size": 2}
        if name in heap_modes:
            if len(arguments) != 1:
                raise ToyError(f"{expression.location}: {name}() expects one heap")
            handle = self._handle_value(arguments[0], expression.location)
            mode = self._constant(heap_modes[name], "i64")
            result = self._new_value("heap_value")
            self._emit(
                f'{result.name} = "toy.heap_query"({handle.name}, {mode.name}) '
                ': (!llvm.ptr, i64) -> i64'
            )
            return Value(result.name, "i64")
        if name == "read_text":
            if arguments:
                raise ToyError(f"{expression.location}: read_text() takes no arguments")
            result = self._new_value("text")
            self._emit(f'{result.name} = "toy.read_text"() : () -> !llvm.ptr')
            return Value(result.name, "!llvm.ptr")
        if name == "put":
            if len(arguments) != 1:
                raise ToyError(f"{expression.location}: put() expects one character code")
            value = arguments[0]
            self._require_type(value, "i64", expression.location)
            character = self._new_value("byte")
            self._emit(f"{character.name} = arith.trunci {value.name} : i64 to i8")
            self._emit(f'"toy.print_char"({character.name}) : (i8) -> ()')
            return Value("", "none")
        if name == "length":
            if len(arguments) == 1 and arguments[0].type.startswith("memref<?x"):
                dimension = self._constant(0, "index")
                size = self._new_value("dimension")
                self._emit(
                    f"{size.name} = memref.dim {arguments[0].name}, {dimension.name} : {arguments[0].type}"
                )
                return self._integer_cast(Value(size.name, "index"), "i64")
            if len(arguments) != 1 or arguments[0].type != "!llvm.ptr":
                raise ToyError(f"{expression.location}: length() expects one string or array")
            result = self._new_value("length")
            self._emit(
                f'{result.name} = "toy.string_length"({arguments[0].name}) '
                ': (!llvm.ptr) -> i64'
            )
            return Value(result.name, "i64")
        if name == "at":
            if len(arguments) != 2 or arguments[0].type != "!llvm.ptr" or arguments[1].type != "i64":
                raise ToyError(f"{expression.location}: at() expects a string and an i64 index")
            result = self._new_value("character")
            self._emit(
                f'{result.name} = "toy.string_at"({arguments[0].name}, {arguments[1].name}) '
                ': (!llvm.ptr, i64) -> i64'
            )
            return Value(result.name, "i64")
        function = self.functions.get(name)
        if function is None:
            raise ToyError(f"{expression.location}: unknown function '{name}'")
        if len(arguments) != len(function.parameters):
            raise ToyError(
                f"{expression.location}: function '{name}' expects {len(function.parameters)} arguments, "
                f"found {len(arguments)}"
            )
        for argument, parameter in zip(arguments, function.parameters, strict=True):
            self._require_type(argument, self._type(parameter.type), expression.location)
        argument_text = ", ".join(argument.name for argument in arguments)
        argument_types = ", ".join(argument.type for argument in arguments)
        return_type = self._type(function.return_type) if function.return_type else None
        if return_type is None:
            self._emit(f"func.call @{name}({argument_text}) : ({argument_types}) -> ()")
            return Value("", "none")
        result = self._new_value(name)
        self._emit(
            f"{result.name} = func.call @{name}({argument_text}) : ({argument_types}) -> {return_type}"
        )
        return Value(result.name, return_type)

    def _emit_text(self, text: str) -> None:
        for byte in text.encode("utf-8"):
            value = self._constant(byte, "i8")
            self._emit(f'"toy.print_char"({value.name}) : (i8) -> ()')

    def _emit_character(self, character: str) -> None:
        self._emit_text(character)

    def _binary(self, operation: str, left: Value, right: Value) -> Value:
        result = self._new_value(operation.rsplit(".", 1)[-1])
        self._emit(f"{result.name} = {operation} {left.name}, {right.name} : {left.type}")
        return Value(result.name, left.type)

    def _generate_min_max(self, name: str, expression: CallExpr) -> Value:
        if not expression.arguments:
            raise ToyError(f"{expression.location}: {name}() expects at least one argument")
        values = [self._generate_expression(argument) for argument in expression.arguments]
        result_type = values[0].type
        if result_type not in {"i8", "i16", "i32", "i64", "i128", "f64"}:
            raise ToyError(f"{expression.location}: {name}() only supports numbers")
        cast_values = [values[0]]
        for value in values[1:]:
            if value.type != result_type:
                if result_type == "f64" and self._is_integer_type(value.type):
                    value = self._numeric_cast(value, "f64", expression.location)
                elif self._is_integer_type(value.type) and result_type != "f64":
                    value = self._integer_cast(value, result_type)
                else:
                    self._require_type(value, result_type, expression.location)
            cast_values.append(value)
        accumulator = cast_values[0]
        for value in cast_values[1:]:
            comparison = self._new_value("compare")
            if result_type == "f64":
                predicate = "olt" if name == "min" else "ogt"
                self._emit(
                    f"{comparison.name} = arith.cmpf {predicate}, {value.name}, {accumulator.name} : f64"
                )
            else:
                predicate = "slt" if name == "min" else "sgt"
                self._emit(
                    f"{comparison.name} = arith.cmpi {predicate}, {value.name}, {accumulator.name} : {result_type}"
                )
            accumulator = self._emit_select(comparison, value, accumulator)
        return accumulator

    def _emit_select(self, predicate: Value, then_value: Value, else_value: Value) -> Value:
        result = self._new_value("select")
        self._emit(f"{result.name} = scf.if {predicate.name} -> ({then_value.type}) {{")
        self.indent += 1
        self._emit(f"scf.yield {then_value.name} : {then_value.type}")
        self.indent -= 1
        self._emit("} else {")
        self.indent += 1
        self._emit(f"scf.yield {else_value.name} : {else_value.type}")
        self.indent -= 1
        self._emit("}")
        return Value(result.name, then_value.type)

    def _generate_index(self, expression: IndexExpr) -> tuple[Value, Value, str]:
        array = self._generate_expression(expression.value)
        element_type = self._array_element_type(array.type, expression.location)
        index = self._generate_expression(expression.index)
        self._require_type(index, "i64", expression.location)
        return array, self._index_cast(index), element_type

    def _array_element_type(self, type_name: str, location: Location) -> str:
        prefix = "memref<?x"
        if not type_name.startswith(prefix) or not type_name.endswith(">"):
            raise ToyError(f"{location}: indexing requires an array")
        return type_name[len(prefix) : -1]

    def _index_cast(self, value: Value) -> Value:
        return self._integer_cast(value, "index")

    def _is_integer_type(self, type_name: str) -> bool:
        return type_name in {"i1", "i8", "i16", "i32", "i64", "i128", "index"}

    def _integer_cast(self, value: Value, target_type: str) -> Value:
        if value.type == target_type:
            return value
        result = self._new_value("cast")
        integer_widths = {"i1": 1, "i8": 8, "i16": 16, "i32": 32, "i64": 64, "i128": 128}
        if value.type == "index" or target_type == "index":
            operation = "arith.index_cast"
        elif value.type in integer_widths and target_type in integer_widths:
            if integer_widths[value.type] < integer_widths[target_type]:
                operation = "arith.extui" if value.type == "i1" else "arith.extsi"
            else:
                operation = "arith.trunci"
        else:
            raise ToyError(f"cannot cast {value.type} to {target_type}")
        self._emit(f"{result.name} = {operation} {value.name} : {value.type} to {target_type}")
        return Value(result.name, target_type)

    def _numeric_cast(self, value: Value, target_type: str, location: Location) -> Value:
        integer_types = {"i1", "i8", "i16", "i32", "i64", "i128", "index"}
        if value.type in integer_types and target_type in integer_types:
            return self._integer_cast(value, target_type)
        if value.type in integer_types and target_type == "f64":
            result = self._new_value("cast")
            self._emit(f"{result.name} = arith.sitofp {value.name} : {value.type} to f64")
            return Value(result.name, "f64")
        if value.type == "f64" and target_type in integer_types:
            result = self._new_value("cast")
            self._emit(f"{result.name} = arith.fptosi {value.name} : f64 to {target_type}")
            return Value(result.name, target_type)
        if value.type == "!llvm.ptr" and target_type == "i64":
            result = self._new_value("ptr_to_int")
            self._emit(f"{result.name} = llvm.ptrtoint {value.name} : !llvm.ptr to i64")
            return Value(result.name, "i64")
        if value.type == "i64" and target_type == "!llvm.ptr":
            result = self._new_value("int_to_ptr")
            self._emit(f"{result.name} = llvm.inttoptr {value.name} : i64 to !llvm.ptr")
            return Value(result.name, "!llvm.ptr")
        if value.type == target_type:
            return value
        raise ToyError(f"{location}: cannot cast {value.type} to {target_type}")

    def _handle_value(self, value: Value, location: Location) -> Value:
        """Coerce a container handle argument: i64 is reinterpreted as a pointer."""
        if value.type == "!llvm.ptr":
            return value
        if value.type == "i64":
            return self._numeric_cast(value, "!llvm.ptr", location)
        raise ToyError(f"{location}: expected a container handle, found {value.type}")

    def _compound_operation(self, operator: str, type_name: str) -> str:
        if type_name == "f64":
            operations = {
                "+=": "arith.addf",
                "-=": "arith.subf",
                "*=": "arith.mulf",
                "/=": "arith.divf",
            }
            if operator not in operations:
                raise ToyError(f"operator '{operator}' is invalid for f64")
            return operations[operator]
        return {
            "+=": "arith.addi",
            "-=": "arith.subi",
            "*=": "arith.muli",
            "/=": "arith.divsi",
            "%=": "arith.remsi",
            "<<=": "arith.shli",
            ">>=": "arith.shrsi",
            "&=": "arith.andi",
            "|=": "arith.ori",
            "^=": "arith.xori",
        }[operator]

    def _constant(self, value: int, type_name: str) -> Value:
        result = self._new_value("c")
        self._emit(f"{result.name} = arith.constant {value} : {type_name}")
        return Value(result.name, type_name)

    def _type(self, type_ref: TypeRef | None) -> str:
        if type_ref is None:
            return "none"
        if type_ref.name == "array" and len(type_ref.arguments) == 1:
            return f"memref<?x{self._type(type_ref.arguments[0])}>"
        if type_ref.arguments or type_ref.name not in SCALAR_TYPES:
            raise ToyError(f"{type_ref.location}: unsupported type '{type_ref.name}'")
        return SCALAR_TYPES[type_ref.name]

    def _source_return_type(self) -> str | None:
        assert self.current_function is not None
        return self._type(self.current_function.return_type) if self.current_function.return_type else None

    def _require_integer(self, value: Value, location: Location) -> None:
        if value.type not in {"i1", "i8", "i16", "i32", "i64", "i128"}:
            raise ToyError(f"{location}: expected integer, found {value.type}")

    def _require_type(self, value: Value, expected: str, location: Location) -> None:
        if value.type != expected:
            raise ToyError(f"{location}: expected {expected}, found {value.type}")

    def _bind(self, name: str, binding: Binding, location: Location) -> None:
        scope = self.scopes[-1]
        if name in scope:
            raise ToyError(f"{location}: duplicate binding '{name}'")
        scope[name] = binding

    def _lookup(self, name: str, location: Location) -> Binding:
        for scope in reversed(self.scopes):
            if name in scope:
                return scope[name]
        raise ToyError(f"{location}: unknown binding '{name}'")

    def _new_value(self, hint: str) -> Value:
        safe_hint = "".join(char if char.isalnum() else "_" for char in hint)
        name = f"%{safe_hint}{self.next_value}"
        self.next_value += 1
        return Value(name, "")

    def _emit(self, text: str) -> None:
        self.lines.append("  " * self.indent + text)


def generate_mlir(program: Program) -> str:
    return MlirGenerator(program).generate()


TOY_ROOT = Path(__file__).resolve().parents[1]
RUNTIME_SOURCES = [
    "runtime/toy_runtime.c",
    "runtime/toy_heap.c",
    "runtime/toy_ordered.c",
]

# Toy dialect lowering followed by the standard MLIR to LLVM conversion chain.
LOWERING_PASSES = [
    "--toy-lower-runtime",
    "--canonicalize",
    "--convert-scf-to-cf",
    "--convert-math-to-llvm",
    "--convert-cf-to-llvm",
    "--convert-index-to-llvm",
    "--convert-arith-to-llvm",
    "--convert-func-to-llvm",
    "--finalize-memref-to-llvm",
    "--reconcile-unrealized-casts",
]


def run(command: list[str], workdir: Path) -> None:
    try:
        subprocess.run(command, cwd=workdir, check=True)
    except subprocess.CalledProcessError as error:
        raise SystemExit(
            f"toyc: command failed ({error.returncode}): {' '.join(str(part) for part in command)}"
        ) from None


def compile_to_assembly(source: Path, workdir: Path, toy_opt: str, emit_mlir: Path | None) -> Path:
    program = load_program(source.read_text(encoding="utf-8"), str(source))
    if emit_mlir is not None:
        emit_mlir.write_text(generate_mlir(program), encoding="utf-8")
    (workdir / "solution.mlir").write_text(generate_mlir(program), encoding="utf-8")

    run([toy_opt, *LOWERING_PASSES, "solution.mlir", "-o", "lowered.mlir"], workdir)
    run(["mlir-translate", "lowered.mlir", "--mlir-to-llvmir", "-o", "solution.ll"], workdir)

    runtime_files: list[str] = []
    for relative in RUNTIME_SOURCES:
        target = Path(relative).name.replace(".c", ".ll")
        run(
            ["clang", "-O3", "-S", "-emit-llvm", "-fno-discard-value-names",
             "-o", target, str(TOY_ROOT / relative)],
            workdir,
        )
        runtime_files.append(target)

    run(["llvm-link", "solution.ll", *runtime_files, "-o", "linked.bc"], workdir)
    run(
        ["opt", "-mcpu=native", "-passes=internalize,default<O3>",
         "-internalize-public-api-list=main", "linked.bc", "-o", "optimized.bc"],
        workdir,
    )
    run(["llc", "-O3", "-mcpu=native", "optimized.bc", "-o", "solution.s"], workdir)
    return workdir / "solution.s"


def main() -> None:
    argument_parser = argparse.ArgumentParser(description="Compile Toy source through MLIR")
    argument_parser.add_argument("source", type=Path)
    argument_parser.add_argument("--dump-ast", action="store_true")
    argument_parser.add_argument("-o", "--output", type=Path, help="build a native executable")
    argument_parser.add_argument("--emit-mlir", type=Path, help="write the pre-lowering Toy MLIR")
    argument_parser.add_argument("--package", type=Path,
                                 help="write a self-contained submission .cpp with the runtime bundled")
    argument_parser.add_argument("--toy-opt", type=Path,
                                 help="path to the toy-opt binary (default: toy-opt on PATH)")
    argument_parser.add_argument("--keep-temps", type=Path, help="keep intermediate files in this directory")
    arguments = argument_parser.parse_args()

    toy_opt = str(arguments.toy_opt) if arguments.toy_opt else shutil.which("toy-opt") or "toy-opt"
    if Path(toy_opt).exists():
        toy_opt = str(Path(toy_opt).resolve())
    elif shutil.which(toy_opt) is None:
        raise SystemExit(f"toyc: toy-opt not found: {toy_opt}")
    if not shutil.which("mlir-translate"):
        raise SystemExit("toyc: mlir-translate not found on PATH (install the system MLIR tools)")
    if not shutil.which("llvm-link") or not shutil.which("opt") or not shutil.which("llc"):
        raise SystemExit("toyc: llvm-link/opt/llc not found on PATH (install the system LLVM tools)")
    if not shutil.which("clang") or not shutil.which("clang++"):
        raise SystemExit("toyc: clang/clang++ not found on PATH")

    try:
        program = load_program(arguments.source.read_text(encoding="utf-8"), str(arguments.source))
    except ToyError as error:
        raise SystemExit(str(error)) from None

    if arguments.dump_ast:
        print(program)
        return

    if arguments.output is None and arguments.package is None and arguments.emit_mlir is None:
        sys.stdout.write(generate_mlir(program))
        return

    workdir = Path(arguments.keep_temps) if arguments.keep_temps else None
    temporary = workdir is None
    if temporary:
        import tempfile
        workdir = Path(tempfile.mkdtemp(prefix="toyc-"))
    assert workdir is not None
    try:
        assembly = compile_to_assembly(
            arguments.source, workdir, toy_opt,
            arguments.emit_mlir,
        )
        if arguments.package is not None:
            run([sys.executable, str(TOY_ROOT / "compiler" / "asm2cpp.py"),
                 str(assembly), str(arguments.package)], workdir)
        elif arguments.output is not None:
            arguments.output.parent.mkdir(parents=True, exist_ok=True)
            run(["clang++", "-lm", str(assembly), "-o", str(arguments.output)], workdir)
    finally:
        if temporary:
            shutil.rmtree(workdir, ignore_errors=True)


if __name__ == "__main__":
    main()