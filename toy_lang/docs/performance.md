# Toy performance notes

The pipeline optimizes the whole program: solution and runtime C sources are
linked into one LLVM module, `internalize`d, and run through
`opt -O3 -mcpu=native`, then `llc -O3 -mcpu=native`. Hot loops compile to
scalar native instructions; containers live in the runtime and are inlinable.

## Measured numbers (this machine, native -O3)

| workload | Toy | g++ -O2 `std::sort` |
|---|---|---|
| heapsort 200k random i64 + checksum pass | 0.030s | 0.036s |

The prelude `sort` is an iterative in-place heapsort written in Toy; even so it
edged out libstdc++ introsort on this input (small cache-friendly working set,
no function-pointer indirection through the comparator).

## Rules that keep solutions fast

- Prefer flat arrays over per-element allocation; `array()` has no free, so
  buffers are hoisted out of loops (e.g. problems 294, 312, 321, 400).
- Use the prelude `fenwick_*`, `dsu_*`, `heap`, `ordered`, `map` instead of
  hand-rolled structures; they lower to straight C with no per-op malloc.
- Bitsets are `i64` words; remember Toy `>>` is arithmetic (mask after shift).
- Interactive problems call `flush()` after each question; `toyc` links `-lm`
  for the `math.*` builtins.
