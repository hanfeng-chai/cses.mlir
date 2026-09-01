#include "Toy/ToyDialect.h"
#include "Toy/ToyOps.h"

using namespace mlir;
using namespace mlir::toy;

#include "Toy/ToyOpsDialect.cpp.inc"

#define GET_OP_CLASSES
#include "Toy/ToyOps.cpp.inc"

void ToyDialect::initialize() {
  addOperations<
#define GET_OP_LIST
#include "Toy/ToyOps.cpp.inc"
      >();
}