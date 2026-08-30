# 265 - Sliding Window Mex

## Problem / 题目
For each window of $k$ elements, output the mex (smallest non-negative integer not present).

对每个 $k$ 元素窗口，输出其 mex（不在其中的最小非负整数）。

## Idea / 思路
The mex of $k$ values is at most $k$, so only values in $[0,k]$ matter. Keep their counts and an ordered set of the values currently absent from the window; the mex is the smallest element of that set. Sliding updates one count in and one out.

$k$ 个值的 mex 至多为 $k$，故只关心 $[0,k]$ 内的值。维护它们的计数与当前缺失值的有序集合；mex 即该集合的最小元素。滑动时更新一进一出的计数。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
