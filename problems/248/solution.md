# 248 - Subarray Squares

## Problem / 题目
Divide an array into $k$ subarrays minimizing the total cost, where each subarray's cost is the square of its sum.

把数组分成 $k$ 个子数组，最小化总代价，每个子数组的代价为其元素和的平方。

## Idea / 思路
Let $dp_j[i]$ be the minimum cost to split the first $i$ elements into $j$ subarrays. With prefix sums, $dp_j[i]=\min_p\big(dp_{j-1}[p]+(\text{pre}_i-\text{pre}_p)^2\big)$. Expanding the square turns each candidate into a line of slope $-2\,\text{pre}_p$ evaluated at $\text{pre}_i$, so the convex hull trick gives each layer in linear time (prefix sums are increasing, so the hull is monotonic).

设 $dp_j[i]$ 为把前 $i$ 个元素分成 $j$ 段的最小代价。借助前缀和，$dp_j[i]=\min_p\big(dp_{j-1}[p]+(\text{pre}_i-\text{pre}_p)^2\big)$。展开平方后每个候选成为斜率 $-2\,\text{pre}_p$ 的直线在 $\text{pre}_i$ 处取值，故凸包优化使每层线性（前缀和递增，凸包单调）。

## Complexity / 复杂度
$O(nk)$. $O(nk)$。
