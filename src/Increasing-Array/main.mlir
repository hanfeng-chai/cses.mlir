func private @get_index() -> index
func private @get_i64() -> i64
func private @put_i64(i64)
func @entry() {
  %0 = @get_index() : () -> index
  %c0 = 0 : index
  %c1 = 1 : index
  %c0_i64 = 0 : i64
  %1:2 = for %arg0 = %c0 to %0 step %c1 iter_args(%arg1 = %c0_i64, %arg2 = %c0_i64) -> (i64, i64) {
    %2 = @get_i64() : () -> i64
    %3 = cmpi ult, %arg2, %2 : i64
    %4:2 = if %3 -> (i64, i64) {
      yield %arg1, %2
    } else {
      %5 = subi %arg2, %2
      %6 = addi %arg1, %5
      yield %6, %arg2
    }
    yield %4#0, %4#1
  }
  @put_i64(%1#0) : (i64) -> ()
  return
}
