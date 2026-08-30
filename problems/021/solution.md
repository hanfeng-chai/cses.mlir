# 021 - Grid Coloring I

## Problem / 题目

Given an $n \times m$ grid coloured with `A`–`D`, recolour every cell so that its new colour differs **both** from its original colour **and** from each of its four neighbours. Print any valid grid, or `IMPOSSIBLE`.

给定一个用 `A`–`D` 染色的 $n \times m$ 网格，重新给每个格子染色，使新颜色**既**不同于原颜色**也**不同于它的四个相邻格。输出任意合法方案，或 `IMPOSSIBLE`。

## Idea / 思路

Process cells in row-major order. For each cell pick the first colour among `A`–`D` that differs from its original colour and from its already-decided **left** and **up** neighbours. There are four colours and at most three forbidden values (original, left, up), so a valid colour always exists — meaning a solution always exists and `IMPOSSIBLE` never happens. The right and down neighbours are taken care of when they themselves are processed (each adjacency is checked from the later cell). Because any valid colouring is accepted, a problem-specific checker (`checker.cpp`) verifies the constraints.

按行优先顺序处理格子。对每个格子，在 `A`–`D` 中选第一个既不同于原颜色、也不同于已确定的**左**、**上**邻居的颜色。四种颜色而最多三个禁用值（原色、左、上），所以合法颜色总是存在——也就是说解必然存在，`IMPOSSIBLE` 永不会发生。右、下邻居会在轮到它们时被处理（每条相邻关系都由较晚的格子检查）。由于任意合法染色都被接受，用题目专用 checker（`checker.cpp`）校验约束。

## Complexity / 复杂度

Every cell tries a constant number of colours, so the algorithm runs in $O(n \cdot m)$.

每个格子只尝试常数种颜色，因此算法运行在 $O(n \cdot m)$。
