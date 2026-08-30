# 030 - Movie Festival

## Problem / 题目

Given the start and end times of $n$ movies, find the maximum number of movies you can watch entirely (no two may overlap).

给定 $n$ 部电影的开始与结束时间，求最多能完整观看多少部电影（任意两部不能重叠）。

## Idea / 思路

This is the classic interval-scheduling problem. Sort the movies by **ending time** and greedily take a movie whenever its start time is at least the end time of the last chosen movie. Always finishing as early as possible leaves the most room for the remaining movies, which is provably optimal.

这是经典的区间调度问题。把电影按**结束时间**排序，每当一部电影的开始时间不早于上一部所选电影的结束时间，就贪心地选它。尽早结束能为后续电影留出最多空间，可证明是最优的。

## Complexity / 复杂度

Sorting dominates, so the time is $O(n \log n)$.

排序是主要开销，因此时间为 $O(n \log n)$。
