# 086 - Message Route

## Problem / 题目

In an undirected graph of $n$ computers and $m$ connections, find a route from computer $1$ to computer $n$ using the fewest computers, and print the route, or `IMPOSSIBLE`.

在一个 $n$ 台计算机、$m$ 条连接的无向图中，找一条从计算机 $1$ 到计算机 $n$、经过计算机数量最少的路线并输出，或输出 `IMPOSSIBLE`。

## Idea / 思路

Minimizing the number of computers on the route is a shortest-path problem on an unweighted graph, solved by breadth-first search from computer $1$. We record each node's predecessor during the BFS, then follow predecessors back from $n$ to $1$ and reverse to obtain the route. Since several shortest routes may exist, a problem-specific checker (`checker.cpp`) accepts any route that starts at $1$, ends at $n$, uses only real edges, and has the optimal length.

让路线上的计算机数最少，是无权图上的最短路问题，用从计算机 $1$ 出发的 BFS 解决。BFS 时记录每个节点的前驱，再从 $n$ 沿前驱回到 $1$ 并反转，即得路线。由于最短路线可能有多条，题目专用 checker（`checker.cpp`）接受任何起于 $1$、止于 $n$、只用真实边、且长度最优的路线。

## Complexity / 复杂度

The BFS runs in $O(n+m)$.

BFS 运行在 $O(n+m)$。
