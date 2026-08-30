# 040 - Distinct Values Subarrays

## Problem / 题目

Count the number of subarrays in which all elements are distinct.

统计所有元素互不相同的子数组的数量。

## Idea / 思路

Use a sliding window. For each right end $r$, keep the smallest left end $l$ such that the window $[l, r]$ has only distinct values — whenever $x[r]$ has appeared at a position $\ge l$, move $l$ just past it. Every subarray ending at $r$ with its left endpoint in $[l, r]$ is valid, contributing $r - l + 1$ to the total.

使用滑动窗口。对每个右端 $r$，维护使窗口 $[l, r]$ 内值互不相同的最小左端 $l$——每当 $x[r]$ 在位置 $\ge l$ 处出现过，就把 $l$ 移到它之后。所有以 $r$ 结尾、左端在 $[l, r]$ 内的子数组都合法，贡献 $r - l + 1$。

## Complexity / 复杂度

Each pointer advances at most $n$ times, so the time is $O(n)$.

每个指针至多前进 $n$ 次，因此时间为 $O(n)$。
