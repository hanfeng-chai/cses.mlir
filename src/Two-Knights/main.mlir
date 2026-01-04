func private @get_index() -> index
func private @put_index(index) -> ()
func @entry() {
  %c1 = 1 : index
  %c2 = 2 : index
  %c4 = 4 : index
  %n = @get_index() : () -> index
  for %i = %c1 to (addi %n, %c1) step %c1 {
    %sum = divui (muli (muli %i, %i), (subi (muli %i, %i), %c1)), %c2
    %ill = muli (muli (subi %i, %c1), (subi %i, %c2)), %c4
    %ans = subi %sum, %ill
    @put_index(%ans) : (index) -> ()
  }
  return
}
