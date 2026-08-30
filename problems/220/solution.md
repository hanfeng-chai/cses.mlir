# 220 - Polygon Area

## Problem / 题目
Compute twice the area of a simple polygon ($2a$, which is an integer).

求一个简单多边形面积的两倍（$2a$，为整数）。

## Idea / 思路
Apply the shoelace formula: $2a=\left|\sum_i (x_i y_{i+1}-x_{i+1} y_i)\right|$. With $n$ up to $1000$ and coordinates up to $10^9$, the sum can reach $\sim10^{21}$, so accumulate in 128-bit.

用鞋带公式：$2a=\left|\sum_i (x_i y_{i+1}-x_{i+1} y_i)\right|$。$n$ 至 $1000$、坐标至 $10^9$ 时和可达 $\sim10^{21}$，故用 128 位累加。

## Complexity / 复杂度
$O(n)$. $O(n)$。
