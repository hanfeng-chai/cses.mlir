add_mlir_dialect_library(MLIRToy
  ToyDialect.cpp
  ToyPasses.cpp

  ADDITIONAL_HEADER_DIRS
  ${PROJECT_SOURCE_DIR}/include/Toy

  DEPENDS
  MLIRToyOpsIncGen
  MLIRToyPassesIncGen

  LINK_LIBS PUBLIC
  MLIRArithDialect
  MLIRFuncDialect
  MLIRIR
  MLIRLLVMDialect
  MLIRTransformUtils
)