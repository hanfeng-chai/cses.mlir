# 019 - Mex Grid Construction

## Problem / 题目

Construct an $n \times n$ grid where each cell holds the smallest non-negative integer that does **not** already appear to its left in the same row or above it in the same column (its *mex*).

构造一个 $n \times n$ 的网格，使每个格子填入**没有**出现在它同行左侧或同列上方的最小非负整数（即它的 *mex*）。

## Idea / 思路

The value forced into cell $(i, j)$ is exactly $i \oplus j$ (bitwise XOR of the row and column indices). This is the classic XOR / Nim-value table: the mex of the already-filled cells in row $i$ and column $j$ always equals $i \oplus j$. So we can skip any simulation and directly print $i \oplus j$ for every cell.

格子 $(i, j)$ 被迫填入的值恰好是 $i \oplus j$（行列下标的按位异或）。这就是经典的 XOR / Nim 值表：同行同列已填格子的 mex 永远等于 $i \oplus j$。因此无需任何模拟，直接对每个格子输出 $i \oplus j$ 即可。

## Complexity / 复杂度

We output $n^2$ numbers, each in $O(1)$, so the total time is $O(n^2)$.

我们输出 $n^2$ 个数，每个 $O(1)$，因此总时间为 $O(n^2)$。
