# 044 - Nested Ranges Check

## Problem / 题目

For each of $n$ ranges, determine whether it contains some other range and whether some other range contains it. Range $[a,b]$ contains $[c,d]$ if $a \le c$ and $d \le b$.

对 $n$ 个区间中的每一个，判断它是否包含另一个区间、以及是否被另一个区间包含。区间 $[a,b]$ 包含 $[c,d]$ 当且仅当 $a \le c$ 且 $d \le b$。

## Idea / 思路

Sort the ranges by $x$ ascending, breaking ties by $y$ descending (so a longer range comes first among equal left ends). Sweeping forward, a range **is contained** if some earlier range (which has $x' \le x$) has $y' \ge y$ — tracked by the running maximum of $y$. Sweeping backward, a range **contains** another if some later range (which has $x' \ge x$) has $y' \le y$ — tracked by the running minimum of $y$.

把区间按 $x$ 升序排序，$x$ 相同则按 $y$ 降序（使相同左端中更长的排前面）。正向扫描时，某区间**被包含**当且仅当前面存在某区间（其 $x' \le x$）满足 $y' \ge y$——用 $y$ 的前缀最大值跟踪。反向扫描时，某区间**包含他人**当且仅当后面存在某区间（其 $x' \ge x$）满足 $y' \le y$——用 $y$ 的后缀最小值跟踪。

## Complexity / 复杂度

Sorting dominates the two linear sweeps, so the time is $O(n \log n)$.

排序是两次线性扫描的主要开销，因此时间为 $O(n \log n)$。
