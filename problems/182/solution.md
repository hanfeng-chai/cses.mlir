# 182 - Graph Paths I

## Problem / 题目
In a directed graph with $n\le 100$ nodes, count the walks from node $1$ to node $n$ using exactly $k$ edges, modulo $10^9+7$.

在有 $n\le 100$ 个结点的有向图中，统计从结点 $1$ 到结点 $n$、恰好经过 $k$ 条边的路径数，模 $10^9+7$。

## Idea / 思路
If $A$ is the adjacency matrix (with multiplicity), entry $(1,n)$ of $A^k$ counts walks of exactly $k$ edges. Compute $A^k$ by fast matrix exponentiation modulo the prime.

设 $A$ 为邻接矩阵（含重边计数），则 $A^k$ 的 $(1,n)$ 元即恰好 $k$ 条边的路径数。用矩阵快速幂在模意义下求 $A^k$。

## Complexity / 复杂度
$O(n^3\log k)$. $O(n^3\log k)$。
