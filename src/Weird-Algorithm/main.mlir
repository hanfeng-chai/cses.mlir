func private @get_i64() -> i64
func private @put_i64(i64)
func @entry() {
  %0 = @get_i64() : () -> i64
  %c1_i64 = 1 : i64
  %c2_i64 = 2 : i64
  %c3_i64 = 3 : i64
  cf.br ^bb1(%0 : i64)
^bb1(%1: i64):  // 3 preds: ^bb0, ^bb3, ^bb4
  @put_i64(%1) : (i64) -> ()
  %2 = cmpi ne, %1, %c1_i64 : i64
  cf.cond_br %2, ^bb2, ^bb5
^bb2:  // pred: ^bb1
  %3 = remui %1, %c2_i64
  %4 = cmpi eq, %3, %c1_i64 : i64
  cf.cond_br %4, ^bb3, ^bb4
^bb3:  // pred: ^bb2
  %5 = muli %1, %c3_i64
  %6 = addi %5, %c1_i64
  cf.br ^bb1(%6 : i64)
^bb4:  // pred: ^bb2
  %7 = divui %1, %c2_i64
  cf.br ^bb1(%7 : i64)
^bb5:  // pred: ^bb1
  return
}
