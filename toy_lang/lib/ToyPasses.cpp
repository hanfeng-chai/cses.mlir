#include "Toy/ToyPasses.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir::toy {
#define GEN_PASS_DEF_TOYLOWERRUNTIME
#include "Toy/ToyPasses.h.inc"

namespace {

func::FuncOp getOrInsertRuntime(Operation *anchor, PatternRewriter &rewriter,
                                StringRef name, TypeRange inputs,
                                TypeRange results) {
  ModuleOp module = anchor->getParentOfType<ModuleOp>();
  if (func::FuncOp function = module.lookupSymbol<func::FuncOp>(name))
    return function;

  OpBuilder::InsertionGuard guard(rewriter);
  rewriter.setInsertionPointToStart(module.getBody());
  auto functionType = rewriter.getFunctionType(inputs, results);
  func::FuncOp function =
      rewriter.create<func::FuncOp>(anchor->getLoc(), name, functionType);
  function.setPrivate();
  return function;
}

class LowerRead : public OpRewritePattern<ReadOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(ReadOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_read_i64", {}, i64);
    func::CallOp call =
        rewriter.create<func::CallOp>(op.getLoc(), runtime, ValueRange{});
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

class LowerPrint : public OpRewritePattern<PrintOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(PrintOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type i1 = rewriter.getI1Type();
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_write_i64", {i64, i1}, {});
    Value newline = rewriter.create<arith::ConstantIntOp>(
        op.getLoc(), op.getNewline() ? 1 : 0, 1);
    rewriter.create<func::CallOp>(op.getLoc(), runtime,
                                  ValueRange{op.getValue(), newline});
    rewriter.eraseOp(op);
    return success();
  }
};

class LowerPrintI128 : public OpRewritePattern<PrintI128Op> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(PrintI128Op op,
                                PatternRewriter &rewriter) const final {
    Type i128 = rewriter.getIntegerType(128);
    Type i1 = rewriter.getI1Type();
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_write_i128", {i128, i1}, {});
    Value newline = rewriter.create<arith::ConstantIntOp>(
        op.getLoc(), op.getNewline() ? 1 : 0, 1);
    rewriter.create<func::CallOp>(op.getLoc(), runtime,
                                  ValueRange{op.getValue(), newline});
    rewriter.eraseOp(op);
    return success();
  }
};

class LowerPopcount : public OpRewritePattern<PopcountOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(PopcountOp op,
                                PatternRewriter &rewriter) const final {
    rewriter.replaceOpWithNewOp<LLVM::CtPopOp>(op, op.getType(),
                                               op.getValue());
    return success();
  }
};

class LowerPrintChar : public OpRewritePattern<PrintCharOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(PrintCharOp op,
                                PatternRewriter &rewriter) const final {
    Type i8 = rewriter.getI8Type();
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_write_byte", i8, {});
    rewriter.create<func::CallOp>(op.getLoc(), runtime, op.getValue());
    rewriter.eraseOp(op);
    return success();
  }
};

class LowerFlush : public OpRewritePattern<FlushOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(FlushOp op,
                                PatternRewriter &rewriter) const final {
    func::FuncOp runtime = getOrInsertRuntime(op, rewriter, "toy_flush", {}, {});
    rewriter.create<func::CallOp>(op.getLoc(), runtime, ValueRange{});
    rewriter.eraseOp(op);
    return success();
  }
};

class LowerPrintF64 : public OpRewritePattern<PrintF64Op> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(PrintF64Op op,
                                PatternRewriter &rewriter) const final {
    Type f64 = rewriter.getF64Type();
    Type i64 = rewriter.getI64Type();
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_write_f64", {f64, i64}, {});
    rewriter.create<func::CallOp>(
        op.getLoc(), runtime, ValueRange{op.getValue(), op.getPrecision()});
    rewriter.eraseOp(op);
    return success();
  }
};

class LowerReadText : public OpRewritePattern<ReadTextOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(ReadTextOp op,
                                PatternRewriter &rewriter) const final {
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_read_text", {}, pointer);
    func::CallOp call =
        rewriter.create<func::CallOp>(op.getLoc(), runtime, ValueRange{});
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

class LowerStringLength : public OpRewritePattern<StringLengthOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(StringLengthOp op,
                                PatternRewriter &rewriter) const final {
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    Type i64 = rewriter.getI64Type();
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_string_length", pointer, i64);
    func::CallOp call =
        rewriter.create<func::CallOp>(op.getLoc(), runtime, op.getValue());
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

class LowerStringAt : public OpRewritePattern<StringAtOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(StringAtOp op,
                                PatternRewriter &rewriter) const final {
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    Type i64 = rewriter.getI64Type();
    Type resultType = rewriter.getI64Type();
    func::FuncOp runtime = getOrInsertRuntime(
      op, rewriter, "toy_string_at", {pointer, i64}, resultType);
    func::CallOp call = rewriter.create<func::CallOp>(
        op.getLoc(), runtime, ValueRange{op.getValue(), op.getIndex()});
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

class LowerMapCreate : public OpRewritePattern<MapCreateOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(MapCreateOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_map_create", i64, pointer);
    func::CallOp call = rewriter.create<func::CallOp>(
        op.getLoc(), runtime, op.getCapacityHint());
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

class LowerMapGet : public OpRewritePattern<MapGetOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(MapGetOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime = getOrInsertRuntime(
        op, rewriter, "toy_map_get", {pointer, i64, i64}, i64);
    func::CallOp call = rewriter.create<func::CallOp>(
        op.getLoc(), runtime,
        ValueRange{op.getMap(), op.getKey(), op.getDefaultValue()});
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

class LowerMapSet : public OpRewritePattern<MapSetOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(MapSetOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime = getOrInsertRuntime(
        op, rewriter, "toy_map_set", {pointer, i64, i64}, {});
    rewriter.create<func::CallOp>(
        op.getLoc(), runtime, ValueRange{op.getMap(), op.getKey(), op.getValue()});
    rewriter.eraseOp(op);
    return success();
  }
};

class LowerOrderedCreate : public OpRewritePattern<OrderedCreateOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(OrderedCreateOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_ordered_create", i64, pointer);
    func::CallOp call = rewriter.create<func::CallOp>(
        op.getLoc(), runtime, op.getCapacityHint());
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

template <typename OpType>
class LowerOrderedUpdate : public OpRewritePattern<OpType> {
public:
  using OpRewritePattern<OpType>::OpRewritePattern;

  LogicalResult matchAndRewrite(OpType op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    StringRef name = std::is_same_v<OpType, OrderedInsertOp>
                         ? "toy_ordered_insert"
                         : "toy_ordered_erase";
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, name, {pointer, i64}, {});
    rewriter.create<func::CallOp>(
        op.getLoc(), runtime, ValueRange{op.getSet(), op.getKey()});
    rewriter.eraseOp(op);
    return success();
  }
};

class LowerOrderedQuery : public OpRewritePattern<OrderedQueryOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(OrderedQueryOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime = getOrInsertRuntime(
        op, rewriter, "toy_ordered_query", {pointer, i64, i64, i64}, i64);
    func::CallOp call = rewriter.create<func::CallOp>(
        op.getLoc(), runtime,
        ValueRange{op.getSet(), op.getKey(), op.getMode(), op.getDefaultValue()});
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

class LowerHeapCreate : public OpRewritePattern<HeapCreateOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(HeapCreateOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_heap_create", i64, pointer);
    func::CallOp call = rewriter.create<func::CallOp>(
        op.getLoc(), runtime, op.getCapacityHint());
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

class LowerHeapPush : public OpRewritePattern<HeapPushOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(HeapPushOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime = getOrInsertRuntime(
        op, rewriter, "toy_heap_push", {pointer, i64, i64}, {});
    rewriter.create<func::CallOp>(
        op.getLoc(), runtime,
        ValueRange{op.getHeap(), op.getFirst(), op.getSecond()});
    rewriter.eraseOp(op);
    return success();
  }
};

class LowerHeapPop : public OpRewritePattern<HeapPopOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(HeapPopOp op,
                                PatternRewriter &rewriter) const final {
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_heap_pop", pointer, {});
    rewriter.create<func::CallOp>(op.getLoc(), runtime, op.getHeap());
    rewriter.eraseOp(op);
    return success();
  }
};

class LowerHeapQuery : public OpRewritePattern<HeapQueryOp> {
public:
  using OpRewritePattern::OpRewritePattern;

  LogicalResult matchAndRewrite(HeapQueryOp op,
                                PatternRewriter &rewriter) const final {
    Type i64 = rewriter.getI64Type();
    Type pointer = LLVM::LLVMPointerType::get(rewriter.getContext());
    func::FuncOp runtime =
        getOrInsertRuntime(op, rewriter, "toy_heap_query", {pointer, i64}, i64);
    func::CallOp call = rewriter.create<func::CallOp>(
        op.getLoc(), runtime, ValueRange{op.getHeap(), op.getMode()});
    rewriter.replaceOp(op, call.getResults());
    return success();
  }
};

class ToyLowerRuntime : public impl::ToyLowerRuntimeBase<ToyLowerRuntime> {
public:
  using impl::ToyLowerRuntimeBase<ToyLowerRuntime>::ToyLowerRuntimeBase;

  void runOnOperation() final {
    RewritePatternSet patterns(&getContext());
    patterns.add<LowerHeapCreate, LowerHeapPop, LowerHeapPush, LowerHeapQuery,
           LowerMapCreate, LowerMapGet, LowerMapSet, LowerOrderedCreate,
           LowerOrderedQuery, LowerOrderedUpdate<OrderedEraseOp>,
                 LowerOrderedUpdate<OrderedInsertOp>, LowerFlush, LowerPrintChar,
                 LowerPrintF64, LowerPrint, LowerPrintI128, LowerPopcount,
           LowerRead, LowerReadText, LowerStringAt, LowerStringLength>(
      &getContext());
    if (failed(applyPatternsGreedily(getOperation(), std::move(patterns))))
      signalPassFailure();
  }
};

} // namespace
} // namespace mlir::toy