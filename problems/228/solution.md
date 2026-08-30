# 228 - Line Segments Trace I

## Problem / 题目
Each segment goes from $(0,y_1)$ to $(m,y_2)$ with integer slope. For each $x=0,1,\dots,m$, print the maximum segment height.

每条线段从 $(0,y_1)$ 到 $(m,y_2)$ 且斜率为整数。对每个 $x=0,1,\dots,m$，输出最大的线段高度。

## Idea / 思路
Each segment is a line $y=\text{slope}\cdot x+y_1$ over $[0,m]$, so we need the upper envelope. Insert all lines into a Li Chao tree over the domain $[0,m]$ and query the maximum at every integer $x$.

每条线段在 $[0,m]$ 上是直线 $y=\text{slope}\cdot x+y_1$，故求上凸包络。把所有直线插入定义域 $[0,m]$ 的 Li Chao 树，在每个整数 $x$ 查询最大值。

## Complexity / 复杂度
$O((n+m)\log m)$. $O((n+m)\log m)$。
