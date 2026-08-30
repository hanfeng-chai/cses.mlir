# 234 - Meet in the Middle

## Problem / 题目
Count the subsets of $n\le 40$ numbers whose sum equals $x$.

统计 $n\le 40$ 个数中和等于 $x$ 的子集个数。

## Idea / 思路
Split the array into two halves of size $\le 20$. Enumerate all $2^{n/2}$ subset sums of each half. Sort the sums of the second half; for each sum $s$ of the first half, count how many sums of the second half equal $x-s$ with binary search.

把数组分成两半（各 $\le 20$ 个）。枚举每半的全部 $2^{n/2}$ 子集和。对第二半的和排序；对第一半的每个和 $s$，用二分查找统计第二半中等于 $x-s$ 的和的个数。

## Complexity / 复杂度
$O(2^{n/2}\,n)$. $O(2^{n/2}\,n)$。
