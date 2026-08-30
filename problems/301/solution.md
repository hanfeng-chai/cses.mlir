# 301 - Even Outdegree Edges

## Problem / 题目
Orient every edge of an undirected graph so each node has even out-degree, or report IMPOSSIBLE.

给无向图每条边定向使每个结点出度为偶，否则 IMPOSSIBLE。

## Idea / 思路
Within a connected component the sum of out-degrees equals its number of edges, so a solution exists iff **every component has an even number of edges**. Build a DFS spanning tree, orient non-tree edges arbitrarily, then process vertices bottom-up: orient each vertex's parent edge to fix that vertex's parity. The root ends up even because the component has an even edge count.

一个连通分量内出度之和等于其边数，故有解当且仅当**每个分量边数为偶**。建 DFS 生成树，非树边任意定向，再自底向上：用每个结点的父边修正其奇偶。根因分量边数为偶而自动为偶。

## Multi-solution / 多解
Any valid orientation is accepted; the checker verifies all out-degrees are even and each edge used once.

任意合法定向均可；checker 验证所有出度为偶且每边恰用一次。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
