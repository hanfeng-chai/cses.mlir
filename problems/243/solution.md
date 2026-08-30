# 243 - Necessary Roads

## Problem / 题目
Find all bridges (edges whose removal disconnects some pair of cities) in a connected undirected graph.

在连通无向图中找出所有桥（删去后会使某两城市不连通的边）。

## Idea / 思路
Run a DFS computing discovery times and low-links. An edge to a child $v$ is a bridge if the lowest reachable discovery time from $v$'s subtree exceeds the discovery time of the parent, i.e. $\text{low}[v] > \text{disc}[u]$. The DFS is implemented iteratively to handle deep graphs.

做一次 DFS 计算发现时间与 low 值。到子结点 $v$ 的边是桥当且仅当 $v$ 子树能回到的最早发现时间大于父结点的发现时间，即 $\text{low}[v] > \text{disc}[u]$。DFS 用迭代实现以应对深图。

## Multi-solution / 多解
The bridges may be printed in any order, so a custom checker compares the participant's set of edges with the jury's set.

桥可任意顺序输出，故自定义 checker 将参赛者的边集合与标程集合比对。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
