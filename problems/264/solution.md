# 264 - Sliding Window Mode

## Problem / 题目
For each window of $k$ elements, output the mode (most frequent value, smallest if tied).

对每个 $k$ 元素窗口，输出众数（出现最多的值，并列时取最小）。

## Idea / 思路
Maintain each value's frequency and, for every frequency, an ordered set of the values currently having that frequency. Track the maximum frequency; when adding or removing shifts a value between frequency buckets, update the maximum. The mode is the smallest value in the bucket of the maximum frequency.

维护每个值的频次，并为每个频次维护当前具有该频次的值的有序集合。跟踪最大频次；增删使值在频次桶间移动时更新最大频次。众数即最大频次桶中的最小值。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
