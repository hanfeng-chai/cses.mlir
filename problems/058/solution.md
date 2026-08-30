# 058 - Movie Festival II

## Problem / 题目

A club of $k$ members attends a festival of $n$ movies; each member watches non-overlapping movies. Maximise the total number of movies the members watch entirely.

一个 $k$ 人俱乐部参加有 $n$ 部电影的影展；每个成员看互不重叠的电影。最大化成员们完整观看的电影总数。

## Idea / 思路

Sort the movies by ending time. Keep a multiset of the members' last finishing times (initially $k$ zeros). For each movie, find the member whose finishing time is the **largest value not exceeding the movie's start** (`upper_bound` then step back); if such a member exists, assign the movie to them, update their finishing time to this movie's end, and count it. Greedily using the member who became free latest (but still in time) keeps the more flexible members available.

把电影按结束时间排序。维护成员上次看完时间的 multiset（初始 $k$ 个 $0$）。对每部电影，找上次看完时间为**不超过该电影开始时间的最大值**的成员（`upper_bound` 再退一格）；若存在，把该电影分给他、把其看完时间更新为本片结束、并计数。贪心地使用"最晚才空闲但仍来得及"的成员，能让更灵活的成员留作后用。

## Complexity / 复杂度

Each movie does an $O(\log k)$ multiset operation, so the total is $O(n \log n)$.

每部电影做一次 $O(\log k)$ 的 multiset 操作，因此总计 $O(n \log n)$。
