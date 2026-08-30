# 094 - Cycle Finding

## Problem / 题目

Given a directed weighted graph (edge weights may be negative), determine whether it contains a negative cycle and, if so, print one.

给定一个有向带权图（边权可为负），判断是否含负环，若有则输出一个。

## Idea / 思路

Run Bellman–Ford with all starting distances set to $0$, so a negative cycle anywhere triggers a relaxation. After $n$ rounds, if some edge $(a,b)$ still relaxes, a negative cycle is reachable through $b$. Following predecessor pointers from $b$ exactly $n$ times lands us on a node guaranteed to be inside the cycle; then we walk predecessors until that node repeats to extract the cycle, and reverse it to the forward direction. Any negative cycle is accepted, so a problem-specific checker (`checker.cpp`) verifies the printed nodes form a closed walk along real edges with strictly negative total weight.

用 Bellman–Ford，把所有起始距离设为 $0$，这样任何位置的负环都会触发松弛。$n$ 轮后若某条边 $(a,b)$ 仍可松弛，则经 $b$ 可达一个负环。从 $b$ 沿前驱走恰好 $n$ 步，必然落到环内某节点；再沿前驱走到该节点重复为止即得环，反转为正向。任意负环都被接受，故题目专用 checker（`checker.cpp`）校验输出节点沿真实边构成闭合环、且总权严格为负。

## Complexity / 复杂度

Bellman–Ford runs in $O(nm)$.

Bellman–Ford 运行在 $O(nm)$。
