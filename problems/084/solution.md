# 084 - Labyrinth

## Problem / 题目

In an $n \times m$ grid with floors, walls, a start `A`, and a target `B`, find a shortest path from `A` to `B` moving in the four directions, and output its length and one move string (`L`/`R`/`U`/`D`), or `NO`.

在一个含地板、墙、起点 `A`、终点 `B` 的 $n \times m$ 网格中，求从 `A` 到 `B` 的一条最短路径（四方向移动），输出长度和一个移动串（`L`/`R`/`U`/`D`），或输出 `NO`。

## Idea / 思路

Breadth-first search from `A` explores cells in order of distance, so the first time we reach `B` we have a shortest path. We store, for each visited cell, the move that first entered it; then we walk backwards from `B` to `A` following these moves and reverse the string to recover the path. Because several shortest paths may exist, we ship a problem-specific checker (`checker.cpp`) that verifies the printed path is legal, stays on floor, ends at `B`, and has the optimal length.

从 `A` 出发的广度优先搜索按距离顺序访问格子，因此第一次到达 `B` 时即得最短路径。我们为每个被访问的格子记录"首次进入它的移动方向"，再从 `B` 沿这些方向回溯到 `A`，把字符串反转即得路径。由于最短路径可能有多条，我们提供题目专用 checker（`checker.cpp`），校验输出路径合法、始终在地板上、终点是 `B`、且长度最优。

## Complexity / 复杂度

The BFS visits each cell once, so the time is $O(nm)$.

BFS 每个格子访问一次，因此时间为 $O(nm)$。
