# 321 - Creating Offices

## Problem / 题目
Choose the maximum number of tree nodes so that every pair is at distance at least $d$.

在树上选最多结点，使任意两点距离至少为 $d$。

## Idea / 思路
Greedily process nodes from deepest to shallowest; select a node iff the nearest already-selected node is at distance $\ge d$ (then the selected node "removes the ball" of radius $d-1$ around it). Deepest-first selection is optimal for trees. To query the nearest selected node and update efficiently, use **centroid decomposition**: each vertex stores its distance to every centroid ancestor, a query takes $\min_c (\text{dist}(v,c)+\text{best}[c])$, and an update relaxes $\text{best}[c]$.

自最深到最浅贪心处理；当最近的已选点距离 $\ge d$ 时选当前点（选后"移除"半径 $d-1$ 的球）。最深优先对树最优。为高效查最近已选点并更新，用**点分治**：每点存到各重心祖先的距离，查询取 $\min_c(\text{dist}(v,c)+\text{best}[c])$，更新松弛 $\text{best}[c]$。

## Multi-solution / 多解
Any maximum valid set is accepted; the checker verifies the size matches the optimum and the pairwise distance is $\ge d$ (via a multi-source BFS).

任意最大合法集合均可；checker 验证规模等于最优且两两距离 $\ge d$（多源 BFS）。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
