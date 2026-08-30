# 104 - Road Reparation

## Problem / 题目

Given $n$ cities and $m$ weighted roads, repair a subset of roads of minimum total cost so that every city is connected, or report `IMPOSSIBLE`.

给定 $n$ 座城市和 $m$ 条带权道路，修复总成本最小的一组道路使所有城市连通，或报告 `IMPOSSIBLE`。

## Idea / 思路

The cheapest connecting subset is a minimum spanning tree. Use Kruskal's algorithm: sort the roads by cost and add each road whose endpoints are in different components (tracked with a disjoint-set union), accumulating its cost. If we add fewer than $n-1$ roads the graph is disconnected and the answer is `IMPOSSIBLE`; otherwise the accumulated cost is the minimum.

最便宜的连通子集就是最小生成树。用 Kruskal 算法：按成本排序道路，对每条两端处于不同分量（用并查集追踪）的道路加入并累加成本。若加入的道路少于 $n-1$ 条则图不连通，答案为 `IMPOSSIBLE`；否则累加成本即为最小值。

## Complexity / 复杂度

Sorting dominates, so the time is $O(m\log m)$.

排序为主，因此时间为 $O(m\log m)$。
