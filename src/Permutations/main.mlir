llvm.mlir.global internal @no_solution("NO SOLUTION\00")
func private @get_index() -> index
func private @put_index(index)
func private @puts(!llvm.ptr)
func @entry() {
  %n = @get_index() : () -> index
  %c1 = 1 : index
  %c2 = 2 : index
  %c3 = 3 : index
  if (ori (cmpi eq, %n, %c2 : index), (cmpi eq, %n, %c3 : index)) {
    @puts((llvm.mlir.addressof @no_solution : !llvm.ptr)) : (!llvm.ptr) -> ()
  } else {
    for %i = %c2 to (addi %n, %c1) step %c2 {
      @put_index(%i) : (index) -> ()
    }
    for %i = %c1 to (addi %n, %c1) step %c2 {
      @put_index(%i) : (index) -> ()
    }
  }
  return
}
