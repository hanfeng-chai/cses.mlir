# 183 - Graph Paths II

## Problem / 题目
In a directed weighted graph with $n\le 100$ nodes, find the minimum total weight of a walk from node $1$ to node $n$ using exactly $k$ edges (or $-1$ if none), with $k$ up to $10^9$.

在有 $n\le 100$ 个结点的有向带权图中，求从结点 $1$ 到结点 $n$、恰好经过 $k$ 条边的路径的最小总权（若不存在则 $-1$），$k$ 可达 $10^9$。

## Idea / 思路
Replace ordinary matrix multiplication with the min-plus (tropical) semiring: "product" is $\min_k(A_{ik}+B_{kj})$, the identity is $0$ on the diagonal and $+\infty$ elsewhere. Then the $(1,n)$ entry of the $k$-th min-plus power is the answer. Use a sentinel $\infty$ larger than the maximum possible path weight $k\cdot c_{\max}\le 10^{18}$.

把普通矩阵乘法换成 min-plus（热带）半环：「乘」为 $\min_k(A_{ik}+B_{kj})$，单位元对角为 $0$、其余为 $+\infty$。则其 $k$ 次幂的 $(1,n)$ 元即答案。哨兵 $\infty$ 要大于最大可能路径权 $k\cdot c_{\max}\le 10^{18}$。

## Complexity / 复杂度
$O(n^3\log k)$. $O(n^3\log k)$。
