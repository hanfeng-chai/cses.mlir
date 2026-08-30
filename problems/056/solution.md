# 056 - Distinct Values Subarrays II

## Problem / 题目

Count the subarrays that contain at most $k$ distinct values.

统计包含至多 $k$ 个不同值的子数组数量。

## Idea / 思路

Slide a window with two pointers, keeping a count of each value inside it and the number of distinct values. Extend the right end; whenever the window holds more than $k$ distinct values, advance the left end (decrementing counts) until at most $k$ remain. Every window ending at $r$ with a valid left end contributes $r - l + 1$ subarrays.

用双指针滑动窗口，记录窗口内每个值的出现次数以及不同值的个数。扩展右端；每当窗口包含超过 $k$ 个不同值，就前移左端（递减计数）直到不超过 $k$ 个。每个以 $r$ 结尾、左端合法的窗口贡献 $r - l + 1$ 个子数组。

## Complexity / 复杂度

Each pointer advances at most $n$ times, so the time is $O(n)$.

每个指针至多前进 $n$ 次，因此时间为 $O(n)$。
