# 275 - Inversion Sorting

## Problem / 题目
Sort a hidden permutation of $1..n$ ($n\le 1000$) by reversing subarrays; after each reversal you are told the current number of inversions. Win when it reaches $0$, using at most $4n$ operations.

通过反转子数组排序 $1..n$（$n\le 1000$）的隐藏排列；每次反转后被告知当前逆序数。逆序数为 $0$ 时获胜，至多 $4n$ 次操作。

## Idea / 思路
Reversing $[i,j]$ changes the inversion count by $\binom{L}{2}-2\cdot(\text{inversions inside }[i,j])$, so reversing and reversing back reveals the number of inversions inside any subarray. Querying every suffix $[i,n]$ yields, by differences, each position's count of smaller elements to its right — the Lehmer code — from which the permutation is reconstructed with an order-statistics Fenwick tree. Finally, knowing the permutation, sort it with at most $n-1$ reversals (selection-style: bring each value to its place). The total is about $3n$ operations.

反转 $[i,j]$ 使逆序数变化 $\binom{L}{2}-2\cdot(\text{区间 }[i,j]\text{ 内逆序数})$，故反转再反转回去即可得任意子数组内的逆序数。询问每个后缀 $[i,n]$，作差得每个位置右侧更小元素的个数（Lehmer 码），再用支持第 $k$ 小的树状数组重建排列。最后已知排列，用至多 $n-1$ 次反转排序（选择式：将每个值移到其位）。总操作约 $3n$ 次。

## Complexity / 复杂度
About $3n$ operations. 约 $3n$ 次操作。
