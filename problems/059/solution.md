# 059 - Maximum Subarray Sum II

## Problem / 题目

Find the maximum sum of a contiguous subarray whose length is between $a$ and $b$ (inclusive).

求长度在 $a$ 到 $b$（含两端）之间的连续子数组的最大和。

## Idea / 思路

Write the subarray sum as $P[r] - P[l]$ using prefix sums, where the length $r - l$ must lie in $[a, b]$, so $l$ ranges over $[r-b,\ r-a]$. As $r$ increases this is a sliding window over $l$; maintain a monotonic deque of prefix indices that yields the minimum $P[l]$ in the window. For each $r$ the best subarray ending there is $P[r]$ minus that window minimum.

用前缀和把子数组的和写成 $P[r] - P[l]$，其中长度 $r - l$ 必须落在 $[a, b]$，于是 $l$ 取值于 $[r-b,\ r-a]$。随着 $r$ 增大这是一个关于 $l$ 的滑动窗口；维护一个单调双端队列给出窗口内最小的 $P[l]$。对每个 $r$，以它结尾的最佳子数组就是 $P[r]$ 减去该窗口最小值。

## Complexity / 复杂度

Each prefix index enters and leaves the deque once, so the time is $O(n)$.

每个前缀下标进出双端队列各一次，因此时间为 $O(n)$。
