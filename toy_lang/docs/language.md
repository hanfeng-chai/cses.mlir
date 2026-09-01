# Toy Language Contract

Toy is a statically typed competitive-programming language implemented on
MLIR. A Toy source file is not C or C++ and the compiler has no C++ source
fallback. C++ solutions in the parent repository are behavioral, complexity,
and performance references only.

## Design goals

1. Source should be no more verbose than the equivalent contest C++.
2. Every abstraction used in a hot loop must lower to scalar LLVM operations
   or to a runtime operation that can be inlined before code generation.
3. Integer arithmetic is explicit and predictable. The default integer type
   is signed `i64`; `i32`, `i128`, `bool`, and `f64` are also primitive types.
4. Bounds checks are enabled in debug builds and removable in release builds.
5. The standard library owns common containers and algorithms; solutions own
   problem-specific algorithms.

## Core syntax

```toy
fn power(base: i64, exponent: i64, modulus: i64) -> i64 {
    var result = 1;
    var value = base;
    var remaining = exponent;
    while remaining > 0 {
        if (remaining & 1) != 0 {
            result = result * value % modulus;
        }
        value = value * value % modulus;
        remaining >>= 1;
    }
    return result;
}

fn main() {
    let n = read();
    println(power(2, n, 1_000_000_007));
}
```

- `let` creates an immutable binding; `var` creates a mutable binding.
- Function parameters and public data layouts have explicit types. Local
  bindings infer their type from the initializer.
- `if`, `while`, and `for value in begin..end` are structured control flow.
- Operators use conventional precedence and signed integer semantics.
- `read()` reads an `i64`; typed input functions cover other primitives and
  strings. `print` and `println` use static overload resolution.

### Currently implemented surface

```toy
fn first_odd(values: array<i64>) -> i64 {
    for i in 0..length(values) {      // half-open range
        if values[i] % 2 == 1 {
            return values[i];         // early return from any nesting depth
        }
    }
    return -1;
}

fn main() {
    let primes = [2, 3, 5, 7];        // array literal
    for i in 9..0 by -2 {             // descending ranges with negative step
        print(i, " ");
        if i == 5 { break; }          // break
        if i % 3 == 0 { continue; }   // continue
    }
    println();
    put('!');                         // char literals
    let half = 0.5;                   // float literals
    let sign = if read() > 0 { 1 } else { -1 };   // if expression (ternary)
    println(min(3, 1, 4), max(3, 1, 4));          // n-ary min/max builtins
}
```

- `break` and `continue` work in `for` and `while` loops at any nesting depth.
- Early `return` works inside loops and conditionals in value and void
  functions.
- Literals: integers with `_` separators, floats (`0.5`), chars (`'a'`,
  escapes `\n \t \r \0 \\ \'`), strings (`"text"` with escapes), array
  literals `[a, b, c]`.
- Comments: `// line` and `/* block */`.
- `min(a, b, ...)` and `max(a, b, ...)` are builtins over integers or `f64`.
- `swap(x, y)` swaps two mutable variables or array elements in place:
  `swap(a, b)`, `swap(values[i], values[j])` — no temporaries, no tuples.
- `flush()` flushes buffered standard output (needed for interactive
  problems before each read of the grader's response).
- Math builtins over `f64`, lowered to the MLIR Math dialect and libm:
  `cos sin tan sqrt log exp floor ceil`.
- Integer literals are `i64`; `i16(..)`, `i32(..)`, `i128(..)`, `f64(..)`
  convert explicitly. Comparisons between integer widths and shift amounts
  coerce automatically; array element stores and compound assignments
  (`x += ...`, `x *= ...`) coerce to the target type.
- `print`/`println` take any number of arguments of any supported type,
  including string literals: `println("? ", mid)`.
- String operations: `read_text()`, `length(s)`, `at(s, i)`, `equal(a, b)`.
- Arrays: `array(n, initial)`, `[e0, e1, ...]`, `length(a)`, `a[i]` read and
  assignment, passed to functions as `array<i64>` (dynamic `memref`).

## Data model

Implemented today (sufficient for all 400 CSES problems):

- signed integer scalars `i8`/`i16`/`i32`/`i64`/`i128`, `bool`, `f64`;
- dynamic one-dimensional arrays (`memref`) with `array(n, initial)`;
- strings as owned byte buffers (`read_text`, `at`, `length`, `equal`);
- hash map (`map`/`map_get`/`map_set`), ordered multiset
  (`ordered`, `ordered_insert/erase`, `ordered_first/last/floor/ceiling/higher`,
  `ordered_size`), binary heap (`heap`, `heap_push`, `heap_pop`,
  `heap_first/second`, `heap_size`) — all C ABI containers, inlinable,
  capacity-hinted;
- functions, recursion, early return, `break`/`continue`, ranges with
  negative step, if-expressions, array/char/float literals, n-ary
  `min`/`max`, `swap`, `popcount`, `flush`, libm math builtins.

Planned (not yet needed by the corpus): tuples and records, multi-
dimensional views, generic functions with monomorphization, and
user-defined containers.

The prelude (`lib/prelude.toy`) is merged into every program and provides:
`sort`, `sort_pairs`, `sort_triples`, `sort_prefix`, `sort_pairs_prefix`,
`lower_bound`, `upper_bound`, `absolute`, `gcd`, `pow_mod`, `matrix_power_mod`,
`fenwick_add/sum/find`, `dsu_find/union`, `kosaraju`, `max_flow` (Dinic),
`root_tree`, `tree_lca`, `integer_sqrt`, `minimum`, `maximum`, `read_array`,
`equal`. Solutions must not redefine these names.

## MLIR pipeline

```text
Toy source
  -> Toy lexer/parser and typed AST
  -> toy + func + scf + arith + memref MLIR
  -> Toy runtime/container lowering
  -> canonicalization and scalar replacement
  -> LLVM dialect
  -> LLVM IR optimization
  -> native executable
```

`toy.read` and `toy.print` are the first implemented dialect operations. The
same dialect owns vectors, strings, and checked indexing as those features are
added. Source-level `let` values stay in SSA form; mutable local scalars use
stack slots that LLVM promotes after lowering.

## Acceptance criteria

For each problem, the Toy implementation must:

- pass every downloaded non-interactive test with the same checker as C++;
- have the same asymptotic time and memory complexity as `main.cpp`;
- stay within a small constant-factor runtime and memory envelope;
- remain comparable in source size and algorithmic structure;
- contain no embedded C++, generated C++ source, or precompiled solution IR.

The six interactive problems use the repository interactor rather than the
batch judge, but still require native Toy solutions.