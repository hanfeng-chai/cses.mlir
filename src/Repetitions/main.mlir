func private @getchar() -> i32
func private @put_i32(i32)
func @entry() {
  %c0_i32 = 0 : i32
  %c1_i32 = 1 : i32
  %c10_i32 = 10 : i32
  %0:4 = while (%arg0 = %c1_i32, %arg1 = %c0_i32, %arg2 = %c0_i32) : (i32, i32, i32) -> (i32, i32, i32, i32) {
    %1 = @getchar() : () -> i32
    %2 = cmpi ne, %1, %c10_i32 : i32
    condition(%2) %arg0, %arg1, %arg2, %1
  } do {
  ^bb0(%arg0: i32, %arg1: i32, %arg2: i32, %arg3: i32):
    %1 = cmpi eq, %arg2, %arg3 : i32
    %2:2 = if %1 -> (i32, i32) {
      %3 = addi %arg1, %c1_i32
      %4 = maxui %arg0, %3
      yield %4, %3
    } else {
      yield %arg0, %c1_i32
    }
    yield %2#0, %2#1, %arg3
  }
  @put_i32(%0#0) : (i32) -> ()
  return
}
