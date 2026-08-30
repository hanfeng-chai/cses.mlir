# 345 - Beautiful Permutation II

## Problem / 题目

A permutation of $1,2,\dots,n$ is beautiful when adjacent values never differ by $1$. Construct the lexicographically smallest beautiful permutation, or report that none exists. Here $n$ can be $10^6$.

若 $1,2,\dots,n$ 的一个排列中，任意相邻元素之差都不为 $1$，则称它是美丽排列。要求构造字典序最小的美丽排列，若不存在则报告无解。这里 $n$ 可达 $10^6$。

## Idea / 思路

For $n=2,3$, no solution exists; $n=1$ is trivial. The exact lexicographically smallest solutions for $4\le n\le9$ are short exceptional cases and are stored directly.

For larger $n$, imagine the usual lexicographic greedy: at each position, try unused values in increasing order and choose the first one from which a completion still exists. Running an exact bitmask completion DP for small $n$ reveals that the greedy prefix becomes periodic:
$$1,3,5,2,4,6,8,10,\quad 7,9,11,13,15,\quad 12,14,16,18,20,\quad 17,19,\dots$$
After the fixed initial prefix, we alternately append blocks of five consecutive unused odd values and five consecutive unused even values. Inside each block adjacent differences are $2$; between blocks the difference is $3$ (for example $10\to7$, $15\to12$, $20\to17$), so the prefix is always beautiful.

Why is this the lexicographic greedy prefix? Within a parity chain, taking the next value of the same parity is the smallest non-adjacent choice. At each block boundary, all smaller unused candidates are either adjacent to the current last value or would isolate the next smallest values into an unavoidable $\pm1$ transition. Switching to the other parity at an offset of $3$ is the first choice that leaves both remaining parity chains connectable. The same argument repeats after shifting every value by $10$, giving the five-odd/five-even periodic structure.

A finite $n$ may cut this infinite pattern in an inconvenient place. To avoid a large collection of end cases, stop generating blocks while at least $15$ numbers remain. Put those remaining numbers in an ordered set and run a lexicographic DFS: try candidates in increasing order, skip values differing by $1$ from the previous value, and backtrack when necessary. The search contains at most $15$ values, so its cost is a constant independent of $n$; it computes the exact lexicographically smallest suffix compatible with the already forced prefix.

This construction was checked against an exact bitmask-DP lexicographic solver for every $n\le16$, and the full $n=10^6$ output was checked to be a permutation with no forbidden adjacent pair.

当 $n=2,3$ 时无解；$n=1$ 显然成立。$4\le n\le9$ 的字典序最小解很短，直接保存这些特殊情况。

对更大的 $n$，考虑标准的字典序贪心：每个位置按升序尝试未使用数字，选择第一个仍能完成后缀的数字。对小 $n$ 用精确位压缩 DP 判断“后缀是否可完成”，可以观察到贪心前缀很快进入周期：
$$1,3,5,2,4,6,8,10,\quad 7,9,11,13,15,\quad 12,14,16,18,20,\quad 17,19,\dots$$
固定初始前缀后，交替加入5个连续未使用奇数和5个连续未使用偶数。每个块内部相邻差为2；块与块之间差为3（例如 $10\to7$、$15\to12$、$20\to17$），所以该前缀始终合法。

为什么它就是字典序贪心前缀？在同一奇偶链中，下一个同奇偶数字是最小的不相邻选择。到达块边界时，更小的未使用候选要么与当前末尾相邻，要么会把之后最小的若干数字隔离，最终被迫产生一次差1的连接。以偏移3切换到另一种奇偶性，是第一个仍能让剩余两条奇偶链继续连接的选择。所有数值整体增加10后，论证完全重复，因此得到“5奇数、5偶数”的周期结构。

有限的 $n$ 可能在周期中间截断，造成许多尾部特判。为避免硬编码大量情况，当剩余数字不超过15个时停止生成完整块。把剩余数字放进有序集合，运行字典序 DFS：按升序尝试候选，跳过与前一个值相差1的数，必要时回溯。搜索规模最多15，与 $n$ 无关，相当于常数；它会求出与已固定前缀兼容的精确字典序最小尾部。

该构造已与精确位压缩 DP 在所有 $n\le16$ 上逐项比较，并对 $n=10^6$ 的完整输出检查了排列性及所有相邻差约束。

## Complexity / 复杂度

Generating and printing the prefix is $O(n)$. The tail DFS handles at most $15$ values, hence constant bounded work. Memory is $O(n)$ for the output and used-value marks.

生成并输出前缀需要 $O(n)$ 时间；尾部 DFS 最多处理15个数，是有界常数工作。输出数组与使用标记占 $O(n)$ 空间。
