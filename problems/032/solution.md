# 032 - Maximum Subarray Sum

## Problem / 题目

Find the maximum sum of a contiguous, non-empty subarray; values may be negative.

求一个连续、非空子数组的最大和；数值可能为负。

## Idea / 思路

Use **Kadane's algorithm**. Keep a running sum and add each element to it; after each addition update the best answer, then reset the running sum to $0$ whenever it drops below $0$ (a negative prefix can only hurt what follows). Initialising the best to $-\infty$ correctly handles an all-negative array, where the answer is the single largest element.

使用 **Kadane 算法**。维护一个滚动和，把每个元素加进去；每次相加后更新最优答案，然后当滚动和降到 $0$ 以下时重置为 $0$（负的前缀只会拖累后面）。把最优答案初始化为 $-\infty$ 可正确处理全负数组——此时答案就是最大的单个元素。

## Complexity / 复杂度

A single pass over the array gives $O(n)$.

对数组单次遍历即可，为 $O(n)$。
