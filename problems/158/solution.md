# 158 - Fixed-Length Paths I

## Problem / 题目

Count the number of distinct paths in a tree that consist of exactly $k$ edges.

统计树中恰好由 $k$ 条边组成的不同路径数。

## Idea / 思路

Use **centroid decomposition**. Repeatedly find a centroid $c$, count the paths of length $k$ that pass through $c$, then recurse into each remaining piece. For a centroid, process its subtrees one by one keeping an array $\text{cnt}[d]$ = number of already-seen nodes at depth $d$ from $c$ (seeded with $\text{cnt}[0]=1$ for $c$ itself). For each node at depth $d$ in the current subtree, add $\text{cnt}[k-d]$ to the answer (pairing it with earlier subtrees), then fold the subtree's depths into $\text{cnt}$. Processing subtrees separately avoids counting two nodes of the same subtree.

使用**点分治**。反复找重心 $c$，统计经过 $c$ 的长度 $k$ 路径，再递归进入各剩余部分。对一个重心，逐个处理它的子树，维护数组 $\text{cnt}[d]$ = 已见的、距 $c$ 深度为 $d$ 的节点数（初值 $\text{cnt}[0]=1$ 表示 $c$ 自身）。对当前子树中深度为 $d$ 的每个节点，把 $\text{cnt}[k-d]$ 累加进答案（与之前的子树配对），再把该子树的深度并入 $\text{cnt}$。分开处理子树避免统计同一子树的两个节点。

## Complexity / 复杂度

Centroid decomposition gives $O(n\log n)$.

点分治为 $O(n\log n)$。
