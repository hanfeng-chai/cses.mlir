llvm.mlir.global internal @yes("YES\00")
llvm.mlir.global internal @no("NO\00")
func private @get_i32() -> i32
func private @put_i32(i32)
func private @puts(!llvm.ptr)
func @entry() {
  %n = @get_i32() : () -> i32
  %c1_i32 = 1 : i32
  %c2_i32 = 2 : i32
  %c3_i32 = 3 : i32
  %sum = divui (muli %n, (addi %n, %c1_i32)), %c2_i32
  if (cmpi eq, (remui %sum, %c2_i32), %c1_i32 : i32) {
    @puts((llvm.mlir.addressof @no : !llvm.ptr)) : (!llvm.ptr) -> ()
  } else {
    @puts((llvm.mlir.addressof @yes : !llvm.ptr)) : (!llvm.ptr) -> ()
    %a = divui %n, %c2_i32
    %b = subi %n, %a
    %m = subi %n, %c1_i32
    @put_i32(%a) : (i32) -> ()
    while (%x = %n, %o = (0 : i1)) : (i32, i1) -> (i32, i1) {
      condition((cmpi sge, %x, %c1_i32 : i32)) %x, %o
    } do {
    ^bb0(%x: i32, %o: i1):
      @put_i32(%x) : (i32) -> ()
      yield (if %o -> i32 {yield (subi %x, %c1_i32)} else {yield (subi %x, %c3_i32)}), (xori %o, (1 : i1))
    }
    @put_i32(%b) : (i32) -> ()
    while (%x = %m, %o = (1 : i1)) : (i32, i1) -> (i32, i1) {
      condition((cmpi sge, %x, %c1_i32 : i32)) %x, %o
    } do {
    ^bb0(%x: i32, %o: i1):
      @put_i32(%x) : (i32) -> ()
      yield (if %o -> i32 {yield (subi %x, %c1_i32)} else {yield (subi %x, %c3_i32)}), (xori %o, (1 : i1))
    }
  }
  return
}
