#!/usr/bin/env python3

import importlib.util
from pathlib import Path
import sys
import unittest


ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("toyc", ROOT / "compiler" / "toyc.py")
assert SPEC is not None and SPEC.loader is not None
TOYC = importlib.util.module_from_spec(SPEC)
sys.modules[SPEC.name] = TOYC
SPEC.loader.exec_module(TOYC)


class FrontendTest(unittest.TestCase):
    def test_bit_strings_uses_logarithmic_loop(self) -> None:
        source_path = ROOT / "test" / "language" / "009-bit-strings.mlir"
        program = TOYC.parse(source_path.read_text(encoding="utf-8"), str(source_path))

        self.assertEqual([function.name for function in program.functions], ["main"])
        statements = program.functions[0].body.statements
        loops = [statement for statement in statements if isinstance(statement, TOYC.WhileStmt)]
        self.assertEqual(len(loops), 1)
        self.assertTrue(
            any(
                isinstance(statement, TOYC.ExprStmt)
                and isinstance(statement.expression, TOYC.AssignExpr)
                and statement.expression.operator == ">>="
                for statement in loops[0].body.statements
            )
        )

    def test_reports_source_location(self) -> None:
        with self.assertRaisesRegex(TOYC.ToyError, r"broken\.mlir:1:25: expected expression"):
            TOYC.parse("fn main() { let value = ; }", "broken.mlir")

    def test_rejects_cpp_source(self) -> None:
        with self.assertRaises(TOYC.ToyError):
            TOYC.parse("#include <bits/stdc++.h>\nint main() {}", "main.toy")

    def test_generates_mlir_dialects(self) -> None:
        source_path = ROOT / "test" / "language" / "009-bit-strings.mlir"
        program = TOYC.parse(source_path.read_text(encoding="utf-8"), str(source_path))
        mlir = TOYC.generate_mlir(program)

        self.assertIn("func.func @main() -> i32", mlir)
        self.assertIn('= "toy.read"() : () -> i64', mlir)
        self.assertIn("scf.while : () -> ()", mlir)
        self.assertIn("arith.shrsi", mlir)
        self.assertIn('"toy.print"', mlir)
        self.assertNotIn("#include", mlir)

    def test_rejects_mutation_of_let_binding(self) -> None:
        program = TOYC.parse("fn main() { let value = 1; value = 2; }", "immutable.mlir")
        with self.assertRaisesRegex(TOYC.ToyError, "cannot assign to immutable binding 'value'"):
            TOYC.generate_mlir(program)

    def test_range_loop_and_formatted_output(self) -> None:
        program = TOYC.parse(
            'fn main() { for value in 2..10 by 2 { print(value, " "); } println("done"); }',
            "format.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn("scf.for", mlir)
        self.assertIn('"toy.print"', mlir)
        self.assertIn('"toy.print_char"', mlir)

    def test_unterminated_string_reports_start(self) -> None:
        with self.assertRaisesRegex(TOYC.ToyError, r"string\.mlir:1:19: unterminated string literal"):
            TOYC.parse('fn main() { print("oops); }', "string.mlir")

    def test_string_runtime_operations(self) -> None:
        program = TOYC.parse(
            "fn main() { let text = read_text(); println(length(text)); }",
            "text.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn('"toy.read_text"', mlir)
        self.assertIn('"toy.string_length"', mlir)

    def test_logical_operators_short_circuit(self) -> None:
        program = TOYC.parse(
            "fn main() { let safe = false && read() > 0; if safe { println(1); } }",
            "logical.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn("= scf.if", mlir)
        self.assertLess(mlir.index("= scf.if"), mlir.index('"toy.read"'))

    def test_array_lowers_to_memref(self) -> None:
        program = TOYC.parse(
            "fn main() { let values = array(4, 0); values[2] = 7; println(values[2]); }",
            "array.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn("memref.alloc", mlir)
        self.assertIn("memref.store", mlir)
        self.assertIn("memref.load", mlir)
        self.assertIn("arith.index_cast", mlir)

    def test_native_prelude_supplies_sort(self) -> None:
        program = TOYC.load_program(
            "fn main() { let values = array(3, 0); sort(values); }",
            "sort.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn("func.func @sort(", mlir)
        self.assertIn("func.call @toy_sift_down", mlir)

    def test_hash_map_operations_use_toy_dialect(self) -> None:
        program = TOYC.parse(
            "fn main() { let table = map(8); map_set(table, 4, 9); println(map_get(table, 4, -1)); }",
            "map.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn('"toy.map_create"', mlir)
        self.assertIn('"toy.map_set"', mlir)
        self.assertIn('"toy.map_get"', mlir)

    def test_ordered_multiset_operations_use_toy_dialect(self) -> None:
        program = TOYC.parse(
            "fn main() { let set = ordered(8); ordered_insert(set, 4); println(ordered_floor(set, 5, -1)); }",
            "ordered.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn('"toy.ordered_create"', mlir)
        self.assertIn('"toy.ordered_insert"', mlir)
        self.assertIn('"toy.ordered_query"', mlir)

    def test_pair_heap_operations_use_toy_dialect(self) -> None:
        program = TOYC.parse(
            "fn main() { let queue = heap(8); heap_push(queue, 4, 2); println(heap_first(queue)); }",
            "heap.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn('"toy.heap_create"', mlir)
        self.assertIn('"toy.heap_push"', mlir)
        self.assertIn('"toy.heap_query"', mlir)

    def test_i128_arithmetic_is_native_mlir(self) -> None:
        program = TOYC.parse(
            "fn main() { let wide = i128(read()) * i128(read()); println(i64(wide % i128(97))); }",
            "wide.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn("arith.extsi", mlir)
        self.assertIn("arith.muli", mlir)
        self.assertIn(": i128", mlir)
        self.assertIn("arith.trunci", mlir)

    def test_f64_arithmetic_and_output_are_native_mlir(self) -> None:
        program = TOYC.parse(
            "fn main() { var probability = f64(1) / f64(6); probability += f64(1); print_fixed(probability, 6); }",
            "float.mlir",
        )
        mlir = TOYC.generate_mlir(program)

        self.assertIn("arith.sitofp", mlir)
        self.assertIn("arith.divf", mlir)
        self.assertIn("arith.addf", mlir)
        self.assertIn('"toy.print_f64"', mlir)

    def test_early_return_inside_if_is_lowered(self) -> None:
        program = TOYC.parse(
            "fn choose(x: i64) -> i64 { if x > 0 { return 1; } println(2); return 3; }",
            "early.mlir",
            require_main=False,
        )
        lowered = TOYC.lower_early_returns(program)
        function = lowered.functions[0]
        self.assertEqual(function.name, "choose")
        mlir = TOYC.generate_mlir(lowered)
        # no func.return may remain inside an scf.if region
        self.assertIn("__ret_flag", mlir)
        self.assertIn("__ret_value", mlir)
        self.assertEqual(mlir.count("func.return"), 1)

    def test_early_return_inside_for_converts_to_while(self) -> None:
        program = TOYC.parse(
            "fn scan(limit: i64) -> i64 { for i in 1..=limit { if i * i >= 9 { return i; } } return 0; }",
            "scan.mlir",
            require_main=False,
        )
        lowered = TOYC.lower_early_returns(program)
        body = lowered.functions[0].body.statements
        # the for loop must have become a while loop
        self.assertTrue(any(isinstance(statement, TOYC.WhileStmt) for statement in body))
        self.assertFalse(any(isinstance(statement, TOYC.ForStmt) for statement in body))
        mlir = TOYC.generate_mlir(lowered)
        self.assertEqual(mlir.count("func.return"), 1)

    def test_early_return_in_void_function(self) -> None:
        program = TOYC.parse(
            "fn stop() { var i = 0; while i < 10 { i += 1; if i == 3 { return; } } println(9); }",
            "stop.mlir",
            require_main=False,
        )
        lowered = TOYC.lower_early_returns(program)
        mlir = TOYC.generate_mlir(lowered)
        self.assertIn("__ret_flag", mlir)
        self.assertEqual(mlir.count("func.return"), 1)

    def test_break_and_continue_are_lowered(self) -> None:
        program = TOYC.parse(
            "fn main() { for i in 1..10 { if i == 3 { break; } print(i); } "
            "for i in 1..10 { if i % 2 == 0 { continue; } print(i); } }",
            "loops.mlir",
        )
        lowered = TOYC.lower_loop_control(program)
        body = lowered.functions[0].body.statements
        # both for loops must have become while loops
        self.assertFalse(any(isinstance(statement, TOYC.ForStmt) for statement in body))
        self.assertIn("__break_", TOYC.generate_mlir(lowered))
        self.assertIn("__continue_", TOYC.generate_mlir(lowered))

    def test_break_outside_loop_is_rejected(self) -> None:
        program = TOYC.parse(
            "fn main() { break; }",
            "bad.mlir",
        )
        with self.assertRaisesRegex(TOYC.ToyError, r"outside of a loop"):
            TOYC.lower_loop_control(program)

    def test_nested_loops_get_distinct_flags(self) -> None:
        program = TOYC.parse(
            "fn main() { for i in 1..5 { for j in 1..5 { if j == 2 { break; } print(j); } print(i); } }",
            "nested.mlir",
        )
        lowered = TOYC.lower_loop_control(program)
        body = lowered.functions[0].body.statements
        # the outer loop keeps scf.for; the inner loop becomes a while
        self.assertTrue(any(isinstance(statement, TOYC.ForStmt) for statement in body))
        mlir = TOYC.generate_mlir(lowered)
        self.assertIn("__break_1", mlir)
        self.assertIn("scf.while", mlir)

    def test_char_and_float_literals(self) -> None:
        program = TOYC.parse(
            "fn main() { put('A'); put('\\n'); let half = 0.5; print_fixed(half, 2); }",
            "literals.mlir",
        )
        mlir = TOYC.generate_mlir(program)
        self.assertIn('arith.constant 65 : i64', mlir)
        self.assertIn(": f64", mlir)

    def test_array_literal(self) -> None:
        program = TOYC.parse(
            "fn main() { let values = [3, 1, 4]; println(values[1]); }",
            "array_lit.mlir",
        )
        mlir = TOYC.generate_mlir(program)
        self.assertIn("memref<?xi64>", mlir)
        self.assertIn("memref.store", mlir)

    def test_if_expression(self) -> None:
        program = TOYC.parse(
            "fn main() { let value = if read() > 0 { 1 } else { -1 }; println(value); }",
            "if_expr.mlir",
        )
        mlir = TOYC.generate_mlir(program)
        self.assertIn("scf.if", mlir)
        self.assertIn("scf.yield", mlir)

    def test_min_max_builtins(self) -> None:
        program = TOYC.parse(
            "fn main() { println(min(3, 1, 4)); println(max(3, 1, 4)); }",
            "minmax.mlir",
        )
        mlir = TOYC.generate_mlir(program)
        self.assertIn("arith.cmpi slt", mlir)
        self.assertIn("arith.cmpi sgt", mlir)

    def test_swap_builtin(self) -> None:
        program = TOYC.parse(
            "fn main() { var a = 3; var b = 4; swap(a, b); let values = [1, 2]; swap(values[0], values[1]); }",
            "swap.mlir",
        )
        mlir = TOYC.generate_mlir(program)
        self.assertIn("memref.load", mlir)
        self.assertIn("memref.store", mlir)

    def test_math_builtins(self) -> None:
        program = TOYC.parse(
            "fn main() { let value = cos(0.5) + sin(0.5) + sqrt(2.0); print_fixed(value, 6); flush(); }",
            "math.mlir",
        )
        mlir = TOYC.generate_mlir(program)
        self.assertIn("math.cos", mlir)
        self.assertIn("math.sin", mlir)
        self.assertIn("math.sqrt", mlir)
        self.assertIn('"toy.flush"', mlir)


if __name__ == "__main__":
    unittest.main()