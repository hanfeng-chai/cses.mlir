#ifndef Toy_PASSES
#define Toy_PASSES

include "mlir/Pass/PassBase.td"

def ToyLowerRuntime : Pass<"toy-lower-runtime", "::mlir::ModuleOp"> {
  let summary = "Lower Toy operations to calls into the C runtime";
  let dependentDialects = [
    "::mlir::arith::ArithDialect",
    "::mlir::func::FuncDialect",
    "::mlir::LLVM::LLVMDialect"
  ];
}

#endif // Toy_PASSES