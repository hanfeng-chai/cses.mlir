# 078 - Projects

## Problem / 题目

Each project has a start day, an end day, and a reward; you may attend only one project per day (a project occupies all days in its inclusive range). Choose non-overlapping projects to maximize total reward.

每个项目有开始日、结束日和报酬；每天只能参加一个项目（项目占用其闭区间内的所有天）。选择互不重叠的项目使总报酬最大。

## Idea / 思路

This is weighted interval scheduling. Sort projects by end day. Let $dp[i]$ be the best reward using the first $i$ projects (in this order). For project $i$ with start day $a$, either skip it ($dp[i-1]$) or take it: add its reward to $dp[\text{lo}]$, where $\text{lo}$ is the number of earlier projects whose end day is strictly before $a$, found by binary search over the sorted end days. Then $dp[i] = \max$ of the two choices.

这是带权区间调度。按结束日排序项目。设 $dp[i]$ 为使用前 $i$ 个项目（此顺序下）的最优报酬。对开始日为 $a$ 的项目 $i$，要么跳过（$dp[i-1]$），要么选它：把它的报酬加到 $dp[\text{lo}]$ 上，其中 $\text{lo}$ 是结束日严格早于 $a$ 的更早项目数，通过对排好序的结束日二分得到。于是 $dp[i] = \max$（两种选择）。

## Complexity / 复杂度

Sorting and $n$ binary searches give $O(n \log n)$.

排序加上 $n$ 次二分，为 $O(n \log n)$。
