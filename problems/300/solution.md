# 300 - Strongly Connected Edges

## Problem / 题目
Orient every edge of an undirected graph so the result is strongly connected, or report IMPOSSIBLE.

给无向图每条边定向使结果强连通，否则报告 IMPOSSIBLE。

## Idea / 思路
By Robbins' theorem this is possible iff the graph is connected and bridgeless. Run a DFS computing discovery/low values: orient tree edges parent→child and back edges descendant→ancestor. A bridge (a tree edge with $\text{low}[child] > \text{disc}[parent]$) or disconnection makes it IMPOSSIBLE. Note: connectivity must be checked by counting DFS roots, not by which vertices were discovered.

由 Robbins 定理，可行当且仅当图连通且无桥。DFS 求 disc/low：树边定向父→子，回边定向后代→祖先。出现桥（树边满足 $\text{low}[\text{子}]>\text{disc}[\text{父}]$）或不连通则 IMPOSSIBLE。注意连通性要数 DFS 根，而非看哪些点被访问。

## Multi-solution / 多解
Any strong orientation is accepted; the checker verifies feasibility and that the result is one SCC.

任意强定向均可；checker 验证可行性且结果为单一强连通分量。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
