# 112 - Teleporters Path

## Problem / 题目

Travel from level $1$ to level $n$ using every teleporter exactly once, printing the sequence of levels, or `IMPOSSIBLE`.

从关卡 $1$ 走到关卡 $n$，每个传送门恰好用一次，输出关卡序列，或 `IMPOSSIBLE`。

## Idea / 思路

This asks for a directed **Eulerian path** from $1$ to $n$. It exists iff level $1$ has one more outgoing than incoming teleporter, level $n$ has one more incoming than outgoing, every other level is balanced, and the relevant edges are connected. We run Hierholzer's algorithm from level $1$; if the resulting path uses all $m$ teleporters (length $m+1$) and starts at $1$ and ends at $n$, it is valid. Any valid path is accepted, so a problem-specific checker (`checker.cpp`) verifies the endpoints and that each teleporter is used once.

这要求一条从 $1$ 到 $n$ 的有向**欧拉路径**。它存在当且仅当关卡 $1$ 出度比入度多 $1$、关卡 $n$ 入度比出度多 $1$、其余关卡出入度相等、且相关边连通。我们从关卡 $1$ 运行 Hierholzer 算法；若得到的路径用满全部 $m$ 个传送门（长度 $m+1$）且起于 $1$ 止于 $n$，则合法。任意合法路径都被接受，故题目专用 checker（`checker.cpp`）校验端点且每个传送门用一次。

## Complexity / 复杂度

Hierholzer's algorithm runs in $O(n+m)$.

Hierholzer 算法运行在 $O(n+m)$。
