#ifndef Toy_DIALECT
#define Toy_DIALECT

include "mlir/IR/OpBase.td"

def Toy_Dialect : Dialect {
  let name = "toy";
  let summary = "High-level operations for the Toy programming language";
  let description = [{
    Toy is a competitive-programming language that lowers its source-level
    operations through MLIR. The dialect models operations that are not
    represented directly by the standard MLIR dialects.
  }];
  let cppNamespace = "::mlir::toy";
}

class Toy_Op<string mnemonic, list<Trait> traits = []>
    : Op<Toy_Dialect, mnemonic, traits>;

#endif // Toy_DIALECT