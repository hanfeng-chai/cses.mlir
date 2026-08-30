# 316 - Graph Coloring

## Problem / 题目
Color the nodes of a graph ($n\le 16$) with the minimum number of colors so adjacent nodes differ.

用最少颜色给图（$n\le 16$）结点染色，使相邻结点颜色不同。

## Idea / 思路
The chromatic number is the minimum number of independent sets that cover all vertices. Precompute which subsets are independent, then DP over subsets: $dp[\text{mask}] = 1 + \min_{s} dp[\text{mask}\setminus s]$ over independent submasks $s$ containing the lowest set bit. Reconstruct the coloring from the chosen independent sets.

色数等于覆盖全部顶点的最少独立集数。预处理各子集是否独立，再做子集 DP：$dp[\text{mask}]=1+\min_{s} dp[\text{mask}\setminus s]$，$s$ 取含最低位的独立子掩码。由所选独立集回溯染色方案。

## Multi-solution / 多解
Any optimal proper coloring is accepted; the checker independently computes the chromatic number ($n\le 16$) and verifies both optimality and properness.

任意最优合法染色均可；checker 独立计算色数（$n\le 16$）并验证最优性与合法性。

## Complexity / 复杂度
$O(3^n)$. $O(3^n)$。
