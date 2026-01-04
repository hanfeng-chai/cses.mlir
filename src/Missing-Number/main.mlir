func private @get_index() -> index
func private @put_index(index)
func @entry() {
  %n = @get_index() : () -> index
  %c1 = 1 : index
  %c2 = 2 : index
  %sum = divui (muli %n, (addi %n, %c1)), %c2
  %ans = for %i = %c1 to %n step %c1 iter_args(%remain = %sum) -> (index) {
    yield (subi %remain, (@get_index() : () -> index))
  }
  @put_index(%ans) : (index) -> ()
  return
}
