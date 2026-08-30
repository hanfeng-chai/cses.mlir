# 139 - Forest Queries II

## Problem / 题目

On an $n \times n$ grid of trees, process queries: toggle a cell between empty and tree, or count the trees inside a rectangle.

在 $n \times n$ 的树网格上处理询问：切换某格的空/树状态，或统计某矩形内的树数。

## Idea / 思路

Because both point updates and rectangle sums are needed, use a **2D Fenwick tree (binary indexed tree)**. Toggling a cell adds $+1$ or $-1$ at that position; a rectangle sum is computed by inclusion–exclusion of four 2D prefix sums. Each 2D Fenwick operation runs in $O(\log^2 n)$.

由于同时需要单点更新与矩形求和，使用**二维树状数组**。切换某格即在该位置加 $+1$ 或 $-1$；矩形和由四个二维前缀和的容斥得到。每个二维树状数组操作为 $O(\log^2 n)$。

## Complexity / 复杂度

Each operation is $O(\log^2 n)$.

每个操作 $O(\log^2 n)$。
