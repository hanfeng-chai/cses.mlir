# 303 - Fixed Length Walk Queries

## Problem / 题目
For an undirected connected graph answer queries: is there a walk of **exactly** $x$ edges from $a$ to $b$?

无向连通图，回答询问：是否存在从 $a$ 到 $b$ 恰好 $x$ 条边的途径？

## Idea / 思路
From each source run a BFS on the layered graph of (node, parity) states, obtaining the shortest **even** and **odd** length walk to every node. Since the graph is connected (every vertex has degree $\ge 1$), any walk can be padded by $+2$ by bouncing on an edge. A query is YES iff $x$ has the right parity and is at least the corresponding shortest even/odd distance.

从每个源在 (结点, 奇偶) 状态的分层图上做 BFS，得到到每点的最短**偶**、**奇**长度途径。因图连通（每点度 $\ge 1$），任意途径可来回一条边加 $2$。询问为 YES 当且仅当 $x$ 奇偶正确且 $\ge$ 对应的最短偶/奇距离。

## Complexity / 复杂度
$O(n(n+m))$ preprocessing, $O(1)$ per query; distances stored as $n\times n$ tables. 预处理 $O(n(n+m))$，每询问 $O(1)$；距离存为 $n\times n$ 表。
