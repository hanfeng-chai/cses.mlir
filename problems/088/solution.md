# 088 - Round Trip

## Problem / 题目

In an undirected graph of $n$ cities and $m$ roads, find a round trip: a cycle that starts and ends at one city, passes through at least two others, with distinct intermediate cities. Print it or `IMPOSSIBLE`.

在一个 $n$ 城市、$m$ 道路的无向图中，找一条环游：从某城出发、经过至少两座其他城市、再回到起点，且中间城市互不相同。输出它或 `IMPOSSIBLE`。

## Idea / 思路

A round trip is just any cycle. Run a depth-first search keeping each node's parent in the DFS tree. When we reach an already-visited node $v$ (other than the immediate parent) from a node $u$, we have found a **back edge**: the cycle is $v \to \dots \to u \to v$, recovered by following parent pointers from $u$ up to $v$. To avoid stack overflow on up to $10^5$ nodes, the DFS is written iteratively. Any valid cycle is accepted, so a problem-specific checker (`checker.cpp`) validates that the printed cities form a closed walk of $\ge 3$ distinct cities along real roads.

环游就是任意一个环。做深度优先搜索，记录每个节点在 DFS 树中的父亲。当从节点 $u$ 到达一个已访问的节点 $v$（且 $v$ 不是直接父亲）时，就找到一条**返祖边**：环为 $v \to \dots \to u \to v$，沿父指针从 $u$ 回溯到 $v$ 即可重建。为避免在多达 $10^5$ 个节点上爆栈，DFS 写成迭代式。任意合法环都被接受，故题目专用 checker（`checker.cpp`）校验输出的城市构成一条沿真实道路、含 $\ge 3$ 个不同城市的闭合环。

## Complexity / 复杂度

The DFS visits each node and edge once, so the time is $O(n+m)$.

DFS 每个节点和边访问一次，因此时间为 $O(n+m)$。
