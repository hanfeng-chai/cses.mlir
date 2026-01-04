func private @get_index() -> index
func private @put_i32(i32)
func @entry() {
  %n = @get_index() : () -> index
  %c1 = 1 : index
  %ans = for %i = %c1 to (addi %n, %c1) step %c1 iter_args(%x = (1: i32)) -> i32 {
    %y = addi %x, %x
    %p = 1000000007 : i32
    yield (select (cmpi ult, %y, %p : i32), %y, (subi %y, %p) : i32)
  }
  @put_i32(%ans) : (i32) -> ()
  return
}
