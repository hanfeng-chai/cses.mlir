llvm.mlir.global internal constant @format_get_i32("%d\00")
llvm.mlir.global internal constant @format_put_i32("%d\0A\00")
llvm.mlir.global internal constant @format_get_i64("%lld\00")
llvm.mlir.global internal constant @format_put_i64("%lld\0A\00")
llvm.func @scanf(!llvm.ptr, ...) -> i32
llvm.func @printf(!llvm.ptr, ...) -> i32
func @get_i32() -> i32 {
  %c1_i32 = 1 : i32
  %0 = llvm.mlir.addressof @format_get_i32 : !llvm.ptr
  %1 = llvm.alloca %c1_i32 x i32 : (i32) -> !llvm.ptr
  %2 = llvm.call @scanf(%0, %1) vararg(!llvm.func<i32 (ptr, ...)>) : (!llvm.ptr, !llvm.ptr) -> i32
  %3 = llvm.load %1 : !llvm.ptr -> i32
  return %3
}
func @get_i64() -> i64 {
  %c1_i32 = 1 : i32
  %0 = llvm.mlir.addressof @format_get_i64 : !llvm.ptr
  %1 = llvm.alloca %c1_i32 x i64 : (i32) -> !llvm.ptr
  %2 = llvm.call @scanf(%0, %1) vararg(!llvm.func<i32 (ptr, ...)>) : (!llvm.ptr, !llvm.ptr) -> i32
  %3 = llvm.load %1 : !llvm.ptr -> i64
  return %3
}
func @get_index() -> index {
  %0 = @get_i64() : () -> i64
  %1 = index_cast %0 : i64 to index
  return %1
}
func @put_i32(%arg0: i32) {
  %0 = llvm.mlir.addressof @format_put_i32 : !llvm.ptr
  %1 = llvm.call @printf(%0, %arg0) vararg(!llvm.func<i32 (ptr, ...)>) : (!llvm.ptr, i32) -> i32
  return
}
func @put_i64(%arg0: i64) {
  %0 = llvm.mlir.addressof @format_put_i64 : !llvm.ptr
  %1 = llvm.call @printf(%0, %arg0) vararg(!llvm.func<i32 (ptr, ...)>) : (!llvm.ptr, i64) -> i32
  return
}
func @put_index(%arg0: index) {
  %0 = index_cast %arg0 : index to i64
  @put_i64(%0) : (i64) -> ()
  return
}
func private @entry()
func @main() -> i32 {
  @entry() : () -> ()
  %c0_i32 = 0 : i32
  return %c0_i32
}
