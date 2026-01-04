func private @get_index() -> index
func private @put_index(index)
func @sqr(%arg0: index) -> index {
  %0 = muli %arg0, %arg0
  return %0
}
func @entry() {
  %n = @get_index() : () -> index
  %c1 = 1 : index
  for %arg0 = %c1 to (addi %n, %c1) step %c1 {
    %i = @get_index() : () -> index
    %j = @get_index() : () -> index
    %i_odd = cmpi eq, (andi %i, %c1), %c1 : index
    %j_odd = cmpi eq, (andi %j, %c1), %c1 : index
    %ans = if (cmpi uge, %i, %j : index) -> index {
      yield (
        if %i_odd  -> index {
          yield (addi (@sqr((subi %i, %c1)) : (index) -> index ), %j)
        } else {
          yield (subi (addi (@sqr(%i) : (index) -> index ), %c1), %j)
        }
      )
    } else {
      yield (
        if %j_odd  -> index {
          yield (subi (addi (@sqr(%j) : (index) -> index ), %c1), %i)
        } else {
          yield (addi (@sqr((subi %j, %c1)) : (index) -> index ), %i)
        }
      )
    }
    @put_index(%ans) : (index) -> ()
  }
  return
}
