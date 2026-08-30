# 091 - Shortest Routes II

## Problem / 题目

Given an undirected weighted graph with $n \le 500$ cities, answer $q$ queries for the shortest distance between two cities (or $-1$ if unreachable).

给定一个 $n \le 500$ 座城市的无向带权图，回答 $q$ 个询问：两城之间的最短距离（不可达则 $-1$）。

## Idea / 思路

Because $n$ is small but there are many queries, precompute all-pairs shortest paths with the Floyd–Warshall algorithm. Initialize the distance matrix from the edges (keeping the smallest weight on multi-edges), then for every intermediate city $k$ relax $d[i][j] = \min(d[i][j],\, d[i][k]+d[k][j])$. Each query is then an $O(1)$ table lookup. Use 64-bit distances and a large "infinity" for unreachable pairs.

由于 $n$ 很小但询问很多，用 Floyd–Warshall 预处理全源最短路。先用边初始化距离矩阵（重边取最小权），再对每个中转城市 $k$ 松弛 $d[i][j] = \min(d[i][j],\, d[i][k]+d[k][j])$。之后每个询问是 $O(1)$ 查表。距离用 64 位，不可达用大"无穷"表示。

## Complexity / 复杂度

Floyd–Warshall is $O(n^3)$ and each query is $O(1)$.

Floyd–Warshall 为 $O(n^3)$，每个询问 $O(1)$。
