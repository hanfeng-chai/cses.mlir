llvm.mlir.global internal @yes("YES\00")
llvm.mlir.global internal @no("NO\00")
func private @get_index() -> index
func private @get_i32() -> i32
func private @puts(!llvm.ptr)
func @entry() {
  %n = @get_index() : () -> index
  %c1 = 1 : index
  for %i = %c1 to (addi %n, %c1) step %c1 {
    %a = @get_i32() : () -> i32
    %b = @get_i32() : () -> i32
    if (ori (ori (cmpi ult, (addi %a, %a), %b : i32), (cmpi ugt, %a, (addi %b, %b) : i32)), (cmpi ne, (remui (addi %a, %b), (3 : i32)), (0 : i32) : i32)) {
      @puts((llvm.mlir.addressof @no : !llvm.ptr)) : (!llvm.ptr) -> ()
    } else {
      @puts((llvm.mlir.addressof @yes : !llvm.ptr)) : (!llvm.ptr) -> ()
    }
  }
  return
}
