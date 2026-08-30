# 164 - Common Divisors

## Problem / 题目
Given $n$ numbers, find the maximum $d$ that divides at least two of them.

给定 $n$ 个数，求能整除其中至少两个数的最大 $d$。

## Idea / 思路
Mark the multiset of values in a frequency array. For each candidate $d$ from the maximum value downward, count how many array elements are multiples of $d$ (sum the frequencies at $d,2d,3d,\dots$). The first $d$ with count $\ge 2$ is the answer.

把值放进频次数组。从最大值往下枚举候选 $d$，统计数组中有多少元素是 $d$ 的倍数（累加 $d,2d,3d,\dots$ 处的频次）。第一个使计数 $\ge 2$ 的 $d$ 即为答案。

## Complexity / 复杂度
$O(M\log M)$ where $M$ is the maximum value. $O(M\log M)$，$M$ 为最大值。
