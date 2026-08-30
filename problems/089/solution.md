# 089 - Monsters

## Problem / 题目

You start at `A` in a grid with monsters `M`. Each turn you and every monster move one step simultaneously. Find a path to any boundary square that is safe no matter how the monsters move, or report `NO`.

你在含怪物 `M` 的网格中起点 `A`。每回合你和所有怪物同时移动一步。求一条到任意边界格、且无论怪物如何移动都安全的路径，或报告 `NO`。

## Idea / 思路

First run a multi-source BFS from all monsters to get $md[x][y]$, the earliest turn a monster can reach each cell. Then BFS from `A`: you may stand on a cell at your arrival time $t$ only if $t < md[x][y]$ (you get there strictly before any monster). The first boundary cell you reach this way is an escape; record predecessors to print the path. The condition guarantees safety even if monsters know your plan. Many escape paths exist, so a problem-specific checker (`checker.cpp`) recomputes the monster times and verifies the path is always one step ahead and ends on the boundary.

先从所有怪物做多源 BFS，得到 $md[x][y]$——怪物到达每格的最早回合。再从 `A` 做 BFS：只有当你到达某格的时间 $t$ 满足 $t < md[x][y]$（你严格早于任何怪物到达）时才能站上去。你这样首次到达的边界格即为逃脱点；记录前驱以输出路径。该条件保证即使怪物预知你的计划也安全。逃脱路径有很多，故题目专用 checker（`checker.cpp`）重算怪物时间并校验路径始终领先一步且终于边界。

## Complexity / 复杂度

Both BFS passes are $O(nm)$.

两次 BFS 都是 $O(nm)$。
