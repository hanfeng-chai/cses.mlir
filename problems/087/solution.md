# 087 - Building Teams

## Problem / 题目

Given $n$ pupils and $m$ friendships, split the pupils into two teams so that no two friends share a team, or report `IMPOSSIBLE`.

给定 $n$ 名学生和 $m$ 对友谊，把学生分成两队，使没有两个朋友在同一队，或报告 `IMPOSSIBLE`。

## Idea / 思路

This asks whether the friendship graph is bipartite. Run a BFS/DFS over each connected component, colouring the start node team $1$ and alternating the team of every neighbour. If we ever find an edge whose endpoints already have the same team, the graph has an odd cycle and the answer is `IMPOSSIBLE`; otherwise the colouring is a valid two-team split. Many colourings are valid, so a problem-specific checker (`checker.cpp`) accepts any assignment where every friendship crosses teams.

这等价于判断友谊图是否二分。对每个连通分量做 BFS/DFS，把起点染成队 $1$，相邻节点交替染队。如果发现某条边两端已是同队，说明存在奇环，答案为 `IMPOSSIBLE`；否则染色就是一个合法的二分。合法染色有很多，故题目专用 checker（`checker.cpp`）接受任何使每对朋友跨队的分配。

## Complexity / 复杂度

The traversal runs in $O(n+m)$.

遍历运行在 $O(n+m)$。
