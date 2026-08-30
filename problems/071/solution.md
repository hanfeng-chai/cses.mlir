# 071 - Rectangle Cutting

## Problem / 题目

Given an $a \times b$ rectangle, repeatedly cut a rectangle into two along an integer line. Find the minimum number of cuts to reduce everything to squares.

给定一个 $a \times b$ 的矩形，每次沿整数线把一个矩形切成两个。求把所有部分都切成正方形所需的最少切割次数.

## Idea / 思路

Let $dp[i][j]$ be the minimum cuts for an $i \times j$ rectangle. A square needs none, so $dp[i][i]=0$. Otherwise try every horizontal cut $dp[k][j] + dp[i-k][j] + 1$ and every vertical cut $dp[i][k] + dp[i][j-k] + 1$, and take the minimum. Filling the table in increasing sizes gives $dp[a][b]$.

设 $dp[i][j]$ 为切完 $i \times j$ 矩形的最少次数。正方形无需切割，故 $dp[i][i]=0$。否则枚举每条水平切割 $dp[k][j] + dp[i-k][j] + 1$ 和每条竖直切割 $dp[i][k] + dp[i][j-k] + 1$，取最小值。按尺寸递增填表即得 $dp[a][b]$。

## Complexity / 复杂度

There are $ab$ states, each trying $O(a+b)$ cuts, so the time is $O(ab(a+b))$.

共 $ab$ 个状态，每个尝试 $O(a+b)$ 种切割，因此时间为 $O(ab(a+b))$。
