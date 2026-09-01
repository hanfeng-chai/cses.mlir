#ifndef Toy_ToyPASSES_H
#define Toy_ToyPASSES_H

#include "Toy/ToyDialect.h"
#include "Toy/ToyOps.h"
#include "mlir/Pass/Pass.h"

namespace mlir::toy {
#define GEN_PASS_DECL
#include "Toy/ToyPasses.h.inc"

#define GEN_PASS_REGISTRATION
#include "Toy/ToyPasses.h.inc"
} // namespace mlir::toy

#endif