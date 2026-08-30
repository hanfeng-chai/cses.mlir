# 053 - Subarray Sums I

## Problem / 题目

Count the subarrays of a **positive**-integer array whose sum is exactly $x$.

统计一个**正整数**数组中和恰好为 $x$ 的子数组数量。

## Idea / 思路

Because all values are positive, the sum of a window grows when the right end extends and shrinks when the left end advances, so it is monotone. Use two pointers: extend the right end adding to the running sum, shrink the left end while the sum exceeds $x$, and count one whenever the sum equals $x$.

由于所有值为正，窗口的和在右端扩展时增大、在左端前移时减小，因此是单调的。用双指针：右端扩展并累加，和超过 $x$ 时收缩左端，每当和等于 $x$ 时计数一次。

## Complexity / 复杂度

Each pointer moves at most $n$ times, so the time is $O(n)$.

每个指针至多移动 $n$ 次，因此时间为 $O(n)$。
