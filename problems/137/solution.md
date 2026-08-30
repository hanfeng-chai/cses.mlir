# 137 - Increasing Array Queries

## Problem / 题目

You may increase array elements by one. For each query $[a,b]$, what is the minimum number of increments to make the subarray non-decreasing?

你可以把数组元素加一。对每个询问 $[a,b]$，把子数组变为非降序所需的最少加一次数是多少？

## Idea / 思路

With only increments, element $i$ must be raised to the running maximum $M_i = \max(x_a,\dots,x_i)$, so the cost is $\sum_{i=a}^{b}(M_i - x_i)$. We answer **offline**, sweeping the left endpoint $a$ from $n$ down to $1$. A monotonic stack maintains, for the current $a$, contiguous segments of equal running-maximum; when $x_a$ is added it overwrites all smaller maxima to its right. A Fenwick tree supporting range-add and range-sum stores the running maxima per position, so each query's $\sum M_i$ over $[a,b]$ is a range sum, and we subtract the static prefix sum of $x$.

只能加一时，元素 $i$ 必须升到前缀最大 $M_i = \max(x_a,\dots,x_i)$，故代价为 $\sum_{i=a}^{b}(M_i - x_i)$。我们**离线**作答，把左端点 $a$ 从 $n$ 扫到 $1$。单调栈为当前 $a$ 维护前缀最大相等的连续段；加入 $x_a$ 时覆盖其右侧所有更小的最大值。一个支持区间加与区间和的树状数组按位置存前缀最大，于是每个询问 $[a,b]$ 上的 $\sum M_i$ 是一次区间和，再减去 $x$ 的静态前缀和。

## Complexity / 复杂度

Each position is pushed and popped once; overall $O((n+q)\log n)$.

每个位置入栈出栈各一次；总体 $O((n+q)\log n)$。
