add_mlir_dialect(ToyOps toy)

set(LLVM_TARGET_DEFINITIONS ToyPasses.td)
mlir_tablegen(ToyPasses.h.inc --gen-pass-decls)
add_public_tablegen_target(MLIRToyPassesIncGen)