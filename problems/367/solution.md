# 367 - Maximum Building I

## Problem / 题目

Given an $n\times m$ forest grid with some squares containing trees, find the largest-area rectangle that avoids every tree.

给定 $n\times m$ 的森林网格，某些格子有树，求不包含任何树的最大矩形面积。

## Idea / 思路

This is the classic **"maximal rectangle in a binary matrix"** problem, solved by reducing it to $n$ instances of "largest rectangle in a histogram" (problem 351). For each row $i$, maintain `h[j]` = the number of consecutive empty squares ending at row $i$, column $j$ (going upward) — i.e. treat row $i$ together with its accumulated height as a histogram. Running the largest-rectangle-in-histogram algorithm (monotonic stack) on this histogram finds the best rectangle whose *bottom* edge is row $i$; taking the best over all rows covers every possible tree-free rectangle, since every such rectangle has some specific bottom row.

这是经典的**"01 矩阵中最大矩形"**问题，做法是把它归约成 $n$ 次"直方图中最大矩形"（第 351 题）。对每一行 $i$，维护 `h[j]` = 以第 $i$ 行第 $j$ 列为底、向上数连续空格子的个数——把第 $i$ 行连同这个累计高度看作一个直方图。在这个直方图上跑一次直方图最大矩形算法（单调栈），就能找到*底边*恰好是第 $i$ 行的最优矩形；对所有行取最大值，就覆盖了每一个无树矩形，因为任何这样的矩形都有一个具体的底行。

## Complexity / 复杂度

$O(nm)$ time (building each row's histogram is $O(m)$, and the histogram algorithm is $O(m)$ amortized), $O(m)$ extra memory.

时间 $O(nm)$（每行构造直方图 $O(m)$，直方图算法均摊 $O(m)$），额外空间 $O(m)$。
