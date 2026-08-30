# 315 - Visiting Cities

## Problem / 题目
On a weighted graph, find all cities that lie on **every** shortest path from $1$ to $n$.

加权图中，求位于从 $1$ 到 $n$ 的**每条**最短路上的所有城市。

## Idea / 思路
Run Dijkstra from $1$ ($d_1$) and from $n$ on the reverse graph ($d_2$). An edge $(u,v,w)$ lies on a shortest path iff $d_1[u]+w+d_2[v]=d_1[n]$; these edges form the shortest-path DAG. Process the DAG in increasing $d_1$ order and compute immediate dominators of $n$ as the LCA (on the partially built dominator tree, via binary lifting) of all DAG-predecessors. The certainly-visited cities are the dominator chain from $n$ to $1$.

从 $1$ 跑 Dijkstra（$d_1$），在反图从 $n$ 跑（$d_2$）。边 $(u,v,w)$ 在某最短路上当且仅当 $d_1[u]+w+d_2[v]=d_1[n]$；这些边构成最短路 DAG。按 $d_1$ 升序处理，$n$ 的直接支配者取所有 DAG 前驱在（增量构建的支配树上，用倍增）的 LCA。必经城市即从 $n$ 到 $1$ 的支配链。

## Complexity / 复杂度
$O((n+m)\log n)$. $O((n+m)\log n)$。
