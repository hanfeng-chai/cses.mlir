# 077 - Increasing Subsequence

## Problem / 题目

Given an array of $n$ integers, find the length of its longest strictly increasing subsequence.

给定一个长度为 $n$ 的数组，求它最长严格递增子序列的长度。

## Idea / 思路

Use patience sorting. Maintain an array `tails`, where `tails[k]` is the smallest possible tail value of an increasing subsequence of length $k+1$. For each element $x$, find the first entry $\ge x$ with a binary search (`lower_bound`): if found, replace it with $x$ (a better, smaller tail for that length); if none exists, append $x$ (it extends the longest subsequence). The final length of `tails` is the answer. Using `lower_bound` (first $\ge x$) enforces *strict* increase.

使用耐心排序。维护数组 `tails`，其中 `tails[k]` 表示长度为 $k+1$ 的递增子序列可能的最小结尾值。对每个元素 $x$，二分查找第一个 $\ge x$ 的位置（`lower_bound`）：若找到则用 $x$ 替换它（为该长度提供更优的更小结尾）；若不存在则把 $x$ 追加到末尾（它延长了最长子序列）。`tails` 的最终长度即答案。用 `lower_bound`（第一个 $\ge x$）保证*严格*递增。

## Complexity / 复杂度

Each element costs one binary search, so the time is $O(n \log n)$.

每个元素一次二分，因此时间为 $O(n \log n)$。
