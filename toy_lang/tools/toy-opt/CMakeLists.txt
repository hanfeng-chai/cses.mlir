set(LIBS
  MLIRArithDialect
  MLIRToy
  MLIRFuncDialect
  MLIRLLVMDialect
  MLIRMemRefDialect
  MLIROptLib
  MLIRRegisterAllDialects
  MLIRRegisterAllPasses
  MLIRSCFDialect
)

add_llvm_executable(toy-opt toy-opt.cpp)
llvm_update_compile_flags(toy-opt)
target_link_libraries(toy-opt PRIVATE ${LIBS})
mlir_check_all_link_libraries(toy-opt)