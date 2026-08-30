# 004 - Increasing Array

## Problem / 题目

We have an array and may increase any element by one per move. We want the array to become non-decreasing (each element at least as large as the previous one) using the minimum number of moves.

我们有一个数组，每次操作可以把任意元素加一。我们希望用最少的操作次数，让数组变成非递减的（每个元素都不小于前一个）。

## Idea / 思路

Process the elements from left to right. Keep track of the largest value seen so far (which is also the smallest value the next element is allowed to take). If the current element is already at least this value, it stays and becomes the new bound. If it is smaller, we must raise it up to the bound, and the cost is the difference. Because raising an element never forces us to touch earlier elements again, this greedy choice is optimal.

从左到右处理每个元素，记录到目前为止的最大值（它同时也是下一个元素被允许取的最小值）。如果当前元素已经不小于这个值，它保持不变并成为新的界限；如果比它小，就必须把它抬高到这个界限，代价就是两者之差。由于抬高一个元素不会迫使我们回头去改前面的元素，所以这个贪心选择是最优的。

## Watch out / 注意

The total number of moves can be as large as about $2 \cdot 10^5 \times 10^9 = 2 \cdot 10^{14}$, so the accumulator must be a `long long`.

操作总数可能高达约 $2 \cdot 10^5 \times 10^9 = 2 \cdot 10^{14}$，因此累加器必须用 `long long`。

## Complexity / 复杂度

A single left-to-right pass: $O(n)$ time and $O(1)$ extra space.

一次从左到右的扫描：时间 $O(n)$，额外空间 $O(1)$。
