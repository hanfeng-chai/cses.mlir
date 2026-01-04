# CSES Problem Set Solutions in MLIR

This repository is an experimental project that solves problems from [CSES Problem Set](https://cses.fi/problemset/) using [MLIR](https://mlir.llvm.org/) (Multi-Level Intermediate Representation).

## Repository Structure

```
.
├── lib/                    # Common MLIR library (I/O functions, etc.)
│   └── common.mlir
├── src/                    # Problem solutions
│   ├── Weird-Algorithm/
│   │   ├── main.mlir       # Solution code
│   │   └── tests.zip       # Test cases (downloaded from CSES)
│   ├── Missing-Number/
│   ├── Increasing-Array/
│   └── ...
├── checker/                # Test checker using testlib.h
├── CMakeLists.txt          # Build system
├── asm2cpp.py              # Assembly to C++ wrapper converter
└── mlir-syntactic-sugar.patch  # MLIR syntax simplification patch
```

## How It Works

Each directory under `src/` represents a CSES problem. To enable judging, download the `tests.zip` file from the CSES website and place it in the corresponding problem directory. Solution files (any `.mlir` files) are placed alongside the zip file. Multiple solutions per problem are supported.

The build system compiles MLIR source files through the following pipeline:
1. **mlir-opt**: Parse and convert to LLVM dialect
2. **mlir-translate**: Translate to LLVM IR
3. **opt + llc**: Optimize and compile to assembly
4. **asm2cpp.py**: Wrap assembly in a C++ raw string literal for final compilation

The generated `.cpp` files can be directly submitted to CSES.

## Build Commands

```bash
# Configure and build
cmake -B build -G Ninja
cd build

# Extract all test cases
ninja mktests

# Judge all problems
ninja judge

# Clean up intermediate files
ninja cleanup

# Remove extracted test files
ninja rmtests
```

### Per-Problem Commands

Commands can be suffixed with problem and solution names:

```bash
ninja mktests-Weird-Algorithm    # Extract tests for specific problem
ninja rmtests-Weird-Algorithm    # Remove tests for specific problem
ninja judge-Weird-Algorithm-main # Judge specific problem with specific solution
```

## MLIR Syntactic Sugar Patch

To simplify MLIR code writing, this project includes a patch (`mlir-syntactic-sugar.patch`) that modifies MLIR's parser to:

- **Omit dialect prefixes**: Write `cmpi` instead of `arith.cmpi`
- **Enable type inference**: Omit explicit type annotations where they can be inferred (e.g., `return %0` instead of `return %0 : i64`)

### Applying the Patch

```bash
# Clone LLVM project
git clone --branch release/21.x --depth 1 https://github.com/llvm/llvm-project.git
cd llvm-project

# Apply the patch
git apply /path/to/mlir-syntactic-sugar.patch

# Build MLIR
cmake -S llvm -B build -G Ninja \
    -DLLVM_ENABLE_PROJECTS="mlir" \
    -DCMAKE_BUILD_TYPE=Release
ninja -C build
```

## LSP Support

For IDE support with the MLIR VS Code extension:

1. Build the patched MLIR as described above
2. Create a symlink to the built `mlir-lsp-server` in this repository's root:
   ```bash
   ln -s /path/to/llvm-project/build/bin/mlir-lsp-server .
   ```
3. Install the [MLIR extension](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-mlir) for VS Code

## Example: Weird Algorithm

The classic Collatz conjecture problem solved in MLIR:

```mlir
func private @get_i64() -> i64
func private @put_i64(i64)

func @entry() {
  %0 = @get_i64() : () -> i64
  %c1_i64 = 1 : i64
  %c2_i64 = 2 : i64
  %c3_i64 = 3 : i64
  cf.br ^bb1(%0 : i64)
^bb1(%1: i64):
  @put_i64(%1) : (i64) -> ()
  %2 = cmpi ne, %1, %c1_i64 : i64
  cf.cond_br %2, ^bb2, ^bb5
^bb2:
  %3 = remui %1, %c2_i64
  %4 = cmpi eq, %3, %c1_i64 : i64
  cf.cond_br %4, ^bb3, ^bb4
^bb3:  // n is odd: n = 3n + 1
  %5 = muli %1, %c3_i64
  %6 = addi %5, %c1_i64
  cf.br ^bb1(%6 : i64)
^bb4:  // n is even: n = n / 2
  %7 = divui %1, %c2_i64
  cf.br ^bb1(%7 : i64)
^bb5:
  return
}
```

## Solved Problems

- Weird Algorithm
- Missing Number
- Repetitions
- Increasing Array
- Permutations
- Number Spiral
- Two Knights
- Two Sets
- Bit Strings
- Trailing Zeros
- Coin Piles

## License

This project is for educational purposes. Feel free to use, modify, and distribute for any purpose.
