# 025 - Distinct Numbers

## Problem / 题目

Given a list of $n$ integers, count how many *distinct* values it contains.

给定一个包含 $n$ 个整数的列表，统计其中有多少个*不同*的值。

## Idea / 思路

Sort the list so that equal values become adjacent, then `unique` collapses each run of equal values into one; the number of remaining elements is the count of distinct values. (A hash set would also work in expected linear time.)

把列表排序，使相等的值相邻，然后用 `unique` 把每段相等的值压成一个，剩下的元素个数就是不同值的数量。（用哈希集合也能在期望线性时间内完成。）

## Complexity / 复杂度

Sorting dominates, so the time is $O(n \log n)$.

排序是主要开销，因此时间为 $O(n \log n)$。
