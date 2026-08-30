# 065 - Grid Paths I

## Problem / 题目

Count the paths from the upper-left to the lower-right square of an $n \times n$ grid, moving only right or down and never stepping on a trap. Print the answer modulo $10^9+7$.

统计 $n \times n$ 网格中从左上角到右下角、只能向右或向下移动且不踩陷阱的路径数。结果对 $10^9+7$ 取模。

## Idea / 思路

Let $dp[i][j]$ be the number of paths reaching cell $(i,j)$. A trap cell has $dp=0$. Otherwise a path arrives either from above or from the left, so $dp[i][j] = dp[i-1][j] + dp[i][j-1]$, with the start cell seeded to $1$. Filling the grid row by row gives $dp[n-1][n-1]$.

设 $dp[i][j]$ 为到达格子 $(i,j)$ 的路径数。陷阱格 $dp=0$；否则路径只能从上方或左方进入，故 $dp[i][j] = dp[i-1][j] + dp[i][j-1]$，起点初始化为 $1$。逐行填表即得 $dp[n-1][n-1]$。

## Complexity / 复杂度

Every cell is computed once, so the time is $O(n^2)$.

每个格子只计算一次，因此时间为 $O(n^2)$。
