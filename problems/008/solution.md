# 008 - Two Sets

## Problem / 题目

We must split the numbers $1, 2, \ldots, n$ into two sets having equal sum, or report that it is impossible.

我们要把数字 $1, 2, \ldots, n$ 划分成两个和相等的集合，或者报告无法做到。

## Idea / 思路

The total sum is $S = \frac{n(n+1)}{2}$. If $S$ is odd it cannot be split into two equal halves, so the answer is `NO`. Otherwise each side must sum to $S/2$. We build the first set greedily by walking from $n$ down to $1$ and taking each number whenever it still fits into the remaining target. Because the values $1, 2, \ldots, n$ are consecutive, this greedy process can always reach the target exactly; the remaining numbers automatically form the second set.

总和是 $S = \frac{n(n+1)}{2}$。如果 $S$ 是奇数，就无法分成相等的两半，答案是 `NO`。否则每一边都要凑到 $S/2$。我们用贪心构造第一个集合：从 $n$ 递减到 $1$，只要某个数还能放进剩余目标里就取它。由于 $1, 2, \ldots, n$ 是连续的，这个贪心过程总能恰好凑到目标；剩下的数自然组成第二个集合。

## Multiple answers / 多解说明

Many valid partitions exist, so we cannot compare against the official output token by token. The accompanying `checker.cpp` (testlib SPJ) verifies that the two printed sets are disjoint, together cover $1..n$ exactly once, and have equal sums — or that a `NO` answer is genuinely correct.

合法的划分有很多种，因此不能逐 token 与官方输出比较。配套的 `checker.cpp`（testlib 特殊评测器）会验证输出的两个集合互不相交、合起来恰好覆盖 $1..n$ 一次、且两者和相等——或者验证 `NO` 答案确实正确。

## Complexity / 复杂度

Building the sets and printing them is a single linear scan: $O(n)$ time, handling $n$ up to $10^6$.

构造集合并输出是一次线性扫描：时间 $O(n)$，可处理 $n$ 达到 $10^6$ 的规模。
