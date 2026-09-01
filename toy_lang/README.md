# Toy

Toy is a compact competitive-programming language implemented on MLIR. It is a
new language with its own hand-written frontend and its own hand-written MLIR
dialect; it is not C++, does not patch MLIR's parser, and does not reuse the
syntactic-sugar prototype in `cses.mlir/` (that directory is reference only).

The language contract is documented in `docs/language.md`; performance rules
and measurements live in `docs/performance.md`.

## Status

All 400 CSES problems have a Toy solution under `problems/NNN/main.toy` and
pass the full local judge (`cmake --build build --target toy-judge`): 4882
non-interactive test results plus 52 interactive runs (problems 270–275,
driven by `tools/interact.py`).

Recent language surface: early `return` at any depth, `break`/`continue`,
descending `for` ranges (`by -1`), `if` expressions, array/char/float
literals, n-ary `min`/`max`, `swap(a, b)`, `flush()`, `popcount`, `print`
with multiple arguments, libm math builtins (`cos sin tan sqrt log exp floor
ceil`) lowered through the MLIR Math dialect (`--convert-math-to-llvm`).

## Layout

```text
compiler/toyc.py       lexer, parser, semantics, MLIR emission, build driver
compiler/asm2cpp.py    wraps final assembly in a C++ raw string for submission
include/Toy/           TableGen dialect and pass definitions
lib/                   Toy dialect registration and runtime-lowering passes
runtime/               C ABI runtime: buffered I/O, hash map, AVL multiset, heap
tools/toy-opt/         optimizer driver with Toy and standard MLIR dialects
test/                  frontend and end-to-end tests
```

## Pipeline

```text
main.toy
  -> toyc.py frontend            (Toy dialect + func/scf/arith/memref MLIR)
  -> toy-opt --toy-lower-runtime  (Toy ops become runtime calls)
  -> toy-opt standard chain       (scf/cf/arith/func/memref -> LLVM dialect)
  -> mlir-translate               (LLVM IR)
  -> clang -emit-llvm             (runtime sources become LLVM IR)
  -> llvm-link                    (solution + runtime linked together)
  -> opt -mcpu=native internalize + default<O3>   (whole-program optimization)
  -> llc -O3 -mcpu=native         (native assembly)
  -> clang++                      (native executable)
```

`--package` produces a single submission-ready C++ file: the final assembly is
wrapped with `__asm__` and the runtime is already linked into it, so nothing
else is needed when submitting to CSES.

## Build

Uses the system LLVM 22 installation:

```bash
cmake -S toy_lang -B toy_lang/build -G Ninja \
      -DMLIR_DIR=/usr/lib64/cmake/mlir \
      -DLLVM_DIR=/usr/lib64/cmake/llvm \
      -DCMAKE_BUILD_TYPE=Release
cmake --build toy_lang/build
ctest --test-dir toy_lang/build --output-on-failure
```

## Compiling a problem

```bash
python3 toy_lang/compiler/toyc.py problems/001/main.toy \
      --toy-opt toy_lang/build/bin/toy-opt \
      -o build/001-toy
python3 toy_lang/compiler/toyc.py problems/001/main.toy \
      --toy-opt toy_lang/build/bin/toy-opt \
      --package /tmp/main.cpp
```

## Example

`problems/009/main.toy` implements modular exponentiation in logarithmic time:

```toy
fn main() {
    var exponent = read();
    let modulus = 1_000_000_007;
    var result = 1;
    var base = 2;
    while exponent > 0 {
        if (exponent & 1) != 0 {
            result = result * base % modulus;
        }
        base = base * base % modulus;
        exponent >>= 1;
    }
    println(result);
}
```
