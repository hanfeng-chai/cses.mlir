#ifndef Toy_OPS
#define Toy_OPS

include "Toy/ToyDialect.td"
include "mlir/Dialect/LLVMIR/LLVMOpBase.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

def Toy_ReadOp : Toy_Op<"read"> {
  let summary = "read a signed 64-bit integer from standard input";
  let results = (outs I64:$result);
  let assemblyFormat = "attr-dict `:` type($result)";
}

def Toy_PrintOp : Toy_Op<"print"> {
  let summary = "write a signed 64-bit integer to standard output";
  let arguments = (ins I64:$value, DefaultValuedAttr<BoolAttr, "false">:$newline);
  let assemblyFormat = "$value (`newline` $newline^)? attr-dict `:` type($value)";
}

def Toy_PrintI128Op : Toy_Op<"print_i128"> {
  let summary = "write a signed 128-bit integer to standard output";
  let arguments = (ins I128:$value, DefaultValuedAttr<BoolAttr, "false">:$newline);
  let assemblyFormat = "$value (`newline` $newline^)? attr-dict `:` type($value)";
}

def Toy_PopcountOp : Toy_Op<"popcount", [Pure]> {
  let summary = "count the number of set bits in a 64-bit integer";
  let arguments = (ins I64:$value);
  let results = (outs I64:$result);
  let assemblyFormat = "$value attr-dict `:` type($value)";
}

def Toy_PrintCharOp : Toy_Op<"print_char"> {
  let summary = "write one byte to standard output";
  let arguments = (ins I8:$value);
  let assemblyFormat = "$value attr-dict `:` type($value)";
}

def Toy_FlushOp : Toy_Op<"flush"> {
  let summary = "flush buffered standard output";
  let assemblyFormat = "attr-dict";
}

def Toy_PrintF64Op : Toy_Op<"print_f64"> {
  let summary = "write an f64 value with fixed decimal precision";
  let arguments = (ins F64:$value, I64:$precision);
  let assemblyFormat = "$value `precision` $precision attr-dict `:` type($value)";
}

def Toy_ReadTextOp : Toy_Op<"read_text"> {
  let summary = "read an owned whitespace-delimited string";
  let results = (outs LLVM_AnyPointer:$result);
  let assemblyFormat = "attr-dict `:` type($result)";
}

def Toy_StringLengthOp : Toy_Op<"string_length", [Pure]> {
  let summary = "return the byte length of a Toy string";
  let arguments = (ins LLVM_AnyPointer:$value);
  let results = (outs I64:$result);
  let assemblyFormat = "$value attr-dict `:` type($value)";
}

def Toy_StringAtOp : Toy_Op<"string_at", [Pure]> {
  let summary = "read one byte from a Toy string";
  let arguments = (ins LLVM_AnyPointer:$value, I64:$index);
  let results = (outs I64:$result);
  let assemblyFormat = "$value `[` $index `]` attr-dict `:` type($value)";
}

def Toy_MapCreateOp : Toy_Op<"map_create"> {
  let summary = "create an i64 to i64 hash map";
  let arguments = (ins I64:$capacityHint);
  let results = (outs LLVM_AnyPointer:$result);
  let assemblyFormat = "$capacityHint attr-dict `:` type($capacityHint) `->` type($result)";
}

def Toy_MapGetOp : Toy_Op<"map_get"> {
  let summary = "read a hash map value or a caller-provided default";
  let arguments = (ins LLVM_AnyPointer:$map, I64:$key, I64:$defaultValue);
  let results = (outs I64:$result);
  let assemblyFormat = "$map `[` $key `]` `default` $defaultValue attr-dict `:` type($map)";
}

def Toy_MapSetOp : Toy_Op<"map_set"> {
  let summary = "insert or replace an i64 hash map entry";
  let arguments = (ins LLVM_AnyPointer:$map, I64:$key, I64:$value);
  let assemblyFormat = "$map `[` $key `]` `=` $value attr-dict `:` type($map)";
}

def Toy_OrderedCreateOp : Toy_Op<"ordered_create"> {
  let summary = "create an ordered i64 multiset";
  let arguments = (ins I64:$capacityHint);
  let results = (outs LLVM_AnyPointer:$result);
  let assemblyFormat = "$capacityHint attr-dict `:` type($capacityHint) `->` type($result)";
}

def Toy_OrderedInsertOp : Toy_Op<"ordered_insert"> {
  let summary = "insert one key into an ordered multiset";
  let arguments = (ins LLVM_AnyPointer:$set, I64:$key);
  let assemblyFormat = "$set `,` $key attr-dict `:` type($set)";
}

def Toy_OrderedEraseOp : Toy_Op<"ordered_erase"> {
  let summary = "erase one matching key from an ordered multiset";
  let arguments = (ins LLVM_AnyPointer:$set, I64:$key);
  let assemblyFormat = "$set `,` $key attr-dict `:` type($set)";
}

def Toy_OrderedQueryOp : Toy_Op<"ordered_query"> {
  let summary = "query an ordered multiset by a compile-time mode";
  let arguments = (ins LLVM_AnyPointer:$set, I64:$key, I64:$mode, I64:$defaultValue);
  let results = (outs I64:$result);
  let assemblyFormat = "$set `,` $key `mode` $mode `default` $defaultValue attr-dict `:` type($set)";
}

def Toy_HeapCreateOp : Toy_Op<"heap_create"> {
  let summary = "create a lexicographic pair min-heap";
  let arguments = (ins I64:$capacityHint);
  let results = (outs LLVM_AnyPointer:$result);
  let assemblyFormat = "$capacityHint attr-dict `:` type($capacityHint) `->` type($result)";
}

def Toy_HeapPushOp : Toy_Op<"heap_push"> {
  let summary = "push an i64 pair into a min-heap";
  let arguments = (ins LLVM_AnyPointer:$heap, I64:$first, I64:$second);
  let assemblyFormat = "$heap `,` $first `,` $second attr-dict `:` type($heap)";
}

def Toy_HeapPopOp : Toy_Op<"heap_pop"> {
  let summary = "remove the smallest pair from a min-heap";
  let arguments = (ins LLVM_AnyPointer:$heap);
  let assemblyFormat = "$heap attr-dict `:` type($heap)";
}

def Toy_HeapQueryOp : Toy_Op<"heap_query"> {
  let summary = "read a component or the size of a pair min-heap";
  let arguments = (ins LLVM_AnyPointer:$heap, I64:$mode);
  let results = (outs I64:$result);
  let assemblyFormat = "$heap `mode` $mode attr-dict `:` type($heap)";
}

#endif // Toy_OPS