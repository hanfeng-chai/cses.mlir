# 131 - Visible Buildings Queries

## Problem / 题目

Standing left of a row of buildings, you see a building if it is taller than all to its left. For each query, if only buildings in $[a,b]$ existed, how many would you see?

站在一排建筑左侧，若某建筑高于它左边所有建筑则可见。对每个询问：若只有 $[a,b]$ 内的建筑存在，能看见几座？

## Idea / 思路

For each building $i$ let $L[i]$ be the nearest index $j<i$ with $h_j \ge h_i$ (using a monotonic stack). Building $i$ is visible in $[a,b]$ exactly when $L[i] < a$ (nothing as tall blocks it inside the window) and $a \le i \le b$. So each query counts indices $i \in [a,b]$ with $L[i] < a$. We answer **offline**: sort queries by $a$ ascending and, with a Fenwick tree over positions, activate each position once $a$ exceeds its $L$ value; the answer is the count of active positions in $[a,b]$.

对每座建筑 $i$，设 $L[i]$ 为最近的满足 $h_j \ge h_i$ 的下标 $j<i$（单调栈求）。$i$ 在 $[a,b]$ 内可见当且仅当 $L[i] < a$（窗口内没有同高或更高者挡住）且 $a \le i \le b$。故每个询问统计 $[a,b]$ 内满足 $L[i] < a$ 的下标。我们**离线**作答：按 $a$ 升序排序询问，用位置上的树状数组在 $a$ 超过某位置的 $L$ 值时激活它；答案为 $[a,b]$ 内活跃位置数。

## Complexity / 复杂度

Sorting plus Fenwick operations give $O((n+q)\log n)$.

排序加树状数组操作为 $O((n+q)\log n)$。
