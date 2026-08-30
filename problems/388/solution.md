# 388 - Grid Puzzle II

## Problem / 题目

Same row/column count constraints as Grid Puzzle I, but now each cell $(i,j)$ has a coin value $c_{ij}$; among all grids satisfying the exact row sums $a_i$ and column sums $b_j$, maximize the total collected value (or report impossible).

约束与 Grid Puzzle I 相同（每行每列的目标 1 的个数），但每个格子 $(i,j)$ 还有一个金币价值 $c_{ij}$；在满足所有行列和约束的网格中，最大化收集到的金币总数（或判断无解）。

## Idea / 思路

This is a weighted transportation problem, solved with **min-cost max-flow**: build a flow network with a source, one node per row, one node per column, and a sink.
- $\text{source}\to \text{row}_i$ with capacity $a_i$, cost $0$;
- $\text{row}_i\to \text{col}_j$ with capacity $1$, cost $-c_{ij}$ (negated, so *minimizing* cost is the same as *maximizing* value);
- $\text{col}_j\to \text{sink}$ with capacity $b_j$, cost $0$.

Run successive shortest augmenting paths (SPFA to handle negative edge costs, since we deliberately use negative costs) until no augmenting path remains. Because every row–column edge has capacity $1$, each augmentation pushes exactly one unit of flow — i.e. selects exactly one grid cell. If the final flow reaches $\sum a_i$ (equivalently $\sum b_j$, guaranteed equal by the constraints), the network is feasible and the maximum value is the negation of the total flow cost; otherwise it's impossible. The chosen cells are read off from which row→column edges end up with zero residual capacity.

Since the optimal grid is generally **not unique** (any grid achieving the reported maximum value while matching all row/column sums is valid), a `checker.cpp` recomputes the row/column sums and the actual collected value from the participant's grid.

这是一个带权运输问题，用**最小费用最大流**求解：建立一个流网络，包含源点、每行一个节点、每列一个节点、汇点。
- $\text{源点}\to\text{行}_i$，容量 $a_i$，费用 $0$；
- $\text{行}_i\to\text{列}_j$，容量 $1$，费用 $-c_{ij}$（取负，这样"最小化费用"等价于"最大化价值"）；
- $\text{列}_j\to\text{汇点}$，容量 $b_j$，费用 $0$。

反复找最短增广路（用 SPFA 处理负权边，因为我们故意使用了负费用）直到找不到增广路为止。由于每条行–列边容量都是1，每次增广恰好推送1单位流量——即恰好选中一个格子。若最终流量达到 $\sum a_i$（与 $\sum b_j$ 相等，由约束保证），则网络可行，最大价值就是总费用取负；否则无解。最终选中的格子由哪些行→列边的剩余容量变为0来确定。

由于最优网格通常**不唯一**（任何满足所有行列和且收集价值等于所报告最大值的网格都算对），`checker.cpp` 会从参赛输出的网格重新计算行列和以及实际收集到的价值。

## Complexity / 复杂度

$n\le 50$: the network has $O(n^2)$ edges and total flow $O(n^2)$; each SPFA is $O(VE)=O(n\cdot n^2)$, giving $O(n^5)$ in the worst case ($\approx 3\times10^8$), comfortably inside the time limit in practice since SPFA rarely hits its worst case on this layered structure.

$n\le50$：网络有 $O(n^2)$ 条边，总流量 $O(n^2)$；每次 SPFA 是 $O(VE)=O(n^3)$，最坏 $O(n^5)\approx3\times10^8$，由于这种分层结构下 SPFA 实际很少达到最坏情况，实测远在时限内。
