func private @get_i32() -> i32
func private @put_i32(i32)
func @entry() {
  %n = @get_i32() : () -> i32
  %0, %ans = while(%x = %n, %acc = (0 : i32)) : (i32, i32) -> (i32, i32) {
    condition((cmpi ne, %x, (0 : i32) : i32)) %x, %acc
  } do {
  ^bb0(%x: i32, %acc: i32):
    %y = divui %x, (5 : i32)
    yield %y, (addi %acc, %y)
  }
  @put_i32(%ans) : (i32) -> ()
  return
}
