# 299 - Acyclic Graph Edges

## Problem / 题目
Orient every edge of an undirected graph so the result is a DAG.

给无向图每条边定向，使结果为有向无环图。

## Idea / 思路
Orient each edge from its lower-numbered endpoint to its higher-numbered endpoint. Any orientation that respects a fixed vertex numbering is acyclic, since every arc increases the index.

把每条边从较小编号端点指向较大编号端点。任何尊重固定结点编号的定向都无环，因为每条弧使编号递增。

## Multi-solution / 多解
Any acyclic orientation is accepted; the checker verifies each input edge is used once and the result has no directed cycle.

任意无环定向均可；checker 验证每条输入边恰用一次且结果无有向环。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
