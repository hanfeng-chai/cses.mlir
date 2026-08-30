# 292 - Distinct Sums Grid

## Problem / 题目
Build an $n\times n$ grid where each value $1..n$ appears $n$ times and the $2n$ row and column sums are all distinct (or IMPOSSIBLE).

构造 $n\times n$ 网格，每个值 $1..n$ 出现 $n$ 次，且 $2n$ 个行、列和互异（或 IMPOSSIBLE）。

## Idea / 思路
For $n\le 3$ there are too few possible sum values, so it is IMPOSSIBLE. For $n\ge 4$, start from a cyclic Latin square (each value appears $n$ times, all sums initially equal) and run a randomized local search: swap the values of two cells (preserving the global counts), maintaining the row/column sums and a count of duplicate sums incrementally, accepting swaps that do not increase the number of collisions until all $2n$ sums are distinct.

$n\le 3$ 时可能的和取值太少，故 IMPOSSIBLE。$n\ge 4$ 时从循环拉丁方出发（每值出现 $n$ 次、初始所有和相等），做随机局部搜索：交换两格的值（保持全局计数），增量维护行列和与重复和计数，接受不增加冲突数的交换，直到 $2n$ 个和全互异。

## Multi-solution / 多解
Any valid grid is accepted; a custom checker verifies value counts and that all $2n$ sums differ.

任意合法网格均可；checker 验证值计数与 $2n$ 个和互异。

## Complexity / 复杂度
Randomized, near $O(n^2)$ in practice. 随机化，实际接近 $O(n^2)$。
