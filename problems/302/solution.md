# 302 - Graph Girth

## Problem / 题目
Find the length of the shortest cycle in an undirected graph, or $-1$ if acyclic.

求无向图最短环的长度，无环则 $-1$。

## Idea / 思路
Run a BFS from every vertex. During the BFS from source $s$, whenever a non-tree edge $(u,v)$ links two already-reached vertices, it closes a cycle of length $\text{dist}[u]+\text{dist}[v]+1$; take the minimum over all sources. With $n\le 2500$, $m\le 5000$ this $O(n\cdot(n+m))$ scan is fast enough.

从每个顶点做 BFS。源 $s$ 的 BFS 中，每遇到连接两个已到达顶点的非树边 $(u,v)$，便闭合一个长度 $\text{dist}[u]+\text{dist}[v]+1$ 的环；对所有源取最小。$n\le 2500$、$m\le 5000$ 时该 $O(n(n+m))$ 足够快。

## Complexity / 复杂度
$O(n(n+m))$. $O(n(n+m))$。
