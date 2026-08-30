# 288 - Monotone Subsequences

## Problem / 题目
Construct a permutation of $1..n$ whose longest monotone (increasing or decreasing) subsequence has exactly $k$ elements, or report IMPOSSIBLE.

构造一个最长单调（递增或递减）子序列恰为 $k$ 的 $1..n$ 排列，或判定 IMPOSSIBLE。

## Idea / 思路
By the Erdős–Szekeres bound the longest monotone subsequence is at least $\lceil\sqrt n\rceil$, so it is IMPOSSIBLE when $k^2<n$. Otherwise split the values into $\lceil n/k\rceil$ blocks, each increasing internally with blocks arranged in decreasing value order. Then the longest increasing run is the maximum block size $k$, and the longest decreasing run is the number of blocks $\lceil n/k\rceil\le k$, so the longest monotone subsequence is exactly $k$.

由 Erdős–Szekeres 界，最长单调子序列至少 $\lceil\sqrt n\rceil$，故 $k^2<n$ 时 IMPOSSIBLE。否则把值分成 $\lceil n/k\rceil$ 块，块内递增、块间按值递减。则最长递增段为最大块长 $k$，最长递减段为块数 $\lceil n/k\rceil\le k$，故最长单调子序列恰为 $k$。

## Multi-solution / 多解
Any valid permutation is accepted; a custom checker verifies it and computes its longest monotone subsequence.

任意合法排列均可；checker 验证并计算其最长单调子序列。

## Complexity / 复杂度
$O(n)$ per test. 每组 $O(n)$。
