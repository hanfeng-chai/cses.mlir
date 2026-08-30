# 151 - Distance Queries

## Problem / 题目

Given a tree, answer queries for the distance between two nodes $a$ and $b$.

给定一棵树，回答两节点 $a$ 与 $b$ 之间距离的询问。

## Idea / 思路

The distance between $a$ and $b$ is $\text{depth}[a] + \text{depth}[b] - 2\,\text{depth}[\text{lca}(a,b)]$, because the path goes up from each node to their lowest common ancestor. We root the tree with a BFS to get depths and parents, build binary-lifting tables, and answer each query with one LCA computation.

$a$ 与 $b$ 的距离为 $\text{depth}[a] + \text{depth}[b] - 2\,\text{depth}[\text{lca}(a,b)]$，因为路径从两节点各自上行到它们的最近公共祖先。我们用 BFS 定根得到深度与父亲，建二进制提升表，每个询问做一次 LCA 即可。

## Complexity / 复杂度

Preprocessing is $O(n\log n)$ and each query is $O(\log n)$.

预处理 $O(n\log n)$，每个询问 $O(\log n)$。
