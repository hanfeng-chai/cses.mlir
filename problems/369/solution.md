# 369 - Cyclic Array

## Problem / 题目

Split a **cyclic** array of $n$ values into the minimum number of contiguous (cyclically) subarrays, each with sum at most $k$.

把一个**环形**数组（$n$ 个值）切成最少数量的连续（环形意义下）子数组，使每段的和都不超过 $k$。

## Idea / 思路

For a fixed *starting cut point*, the linear version of this problem (minimum partition of a line into sum-$\le k$ chunks) is solved by a simple greedy: from the current position, extend the chunk as far right as possible while the sum stays $\le k$ (values are positive, so the reachable end point only ever moves forward as the start advances — a standard two-pointer sweep). The hard part is that **the best starting cut point isn't fixed** — the sample needs the cut right after index $0$ to reach the optimal $3$ chunks, while cutting at index $0$ itself needs $4$.

To search all $n$ possible starting points efficiently, double the array (length $2n$, so every cyclic chunk becomes an ordinary contiguous range) and precompute, for every position $s$ in the doubled array, `jump[s]` = the furthest position reachable by one greedy chunk starting at $s$ (via the two-pointer sweep over the doubled array, $O(n)$ total). Then build a **binary-lifting table**: `jump2[level][s]` = the result of applying `jump` $2^{\text{level}}$ times from $s$. For each candidate start $s\in[0,n)$, use the table to count, in $O(\log n)$, how many chunks are needed to advance from $s$ to at least $s+n$ (i.e. cover a full cycle) — exactly like the standard "count steps to reach a threshold" binary-lifting pattern. Take the minimum count over all $n$ starting points.

*Sanity check:* with $x=[2,2,2,1,3,1,2,1]$, $k=5$, starting the cut right after index $0$ gives chunks $(2,2,1),(3,1),(2,1,2\text{ wrapping to index }0)$ — sums $5,4,5$, all $\le k$, using $3$ chunks total, matching the sample.

对固定的*起点切口*，这个问题的线性版（把一条直线切成和 $\le k$ 的若干段，段数最少）用简单贪心解决：从当前位置尽可能往右扩展，只要和仍 $\le k$（值都是正数，所以能到达的终点只会随起点右移而单调右移——标准双指针扫描）。难点在于**最优的起点切口并不固定**——样例需要在下标 $0$ 之后切开才能达到最优的 $3$ 段，而在下标 $0$ 处切开则需要 $4$ 段。

为了高效地枚举全部 $n$ 个可能的起点，把数组翻倍（长度 $2n$，这样每个环形段都变成普通的连续区间），预处理翻倍数组上每个位置 $s$ 的 `jump[s]` = 从 $s$ 开始贪心扩展一段能到达的最远位置（在翻倍数组上做双指针扫描，总共 $O(n)$）。然后建一张**倍增表**：`jump2[level][s]` = 从 $s$ 出发应用 `jump` $2^{\text{level}}$ 次的结果。对每个候选起点 $s\in[0,n)$，用这张表在 $O(\log n)$ 内数出从 $s$ 前进到至少 $s+n$（即覆盖完整一圈）需要多少段——正是标准的"倍增求达到阈值所需步数"套路。对全部 $n$ 个起点取最小值。

*验证：* $x=[2,2,2,1,3,1,2,1]$，$k=5$，在下标 $0$ 之后切开得到段 $(2,2,1),(3,1),(2,1,2\text{ 环绕到下标 }0)$——和分别为 $5,4,5$，都 $\le k$，共 $3$ 段，与样例一致。

## Complexity / 复杂度

$O(n)$ to build the doubled array and the base jump function, $O(n\log n)$ to build the binary-lifting table and query all $n$ starting points.

构造翻倍数组与基础跳转函数 $O(n)$，构建倍增表并对全部 $n$ 个起点查询 $O(n\log n)$。
