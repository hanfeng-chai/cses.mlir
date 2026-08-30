# 031 - Sum of Two Values

## Problem / 题目

Find two values at distinct positions whose sum is $x$, printing their positions (any valid pair), or `IMPOSSIBLE` if none exist.

找出位于不同位置、和为 $x$ 的两个值，输出它们的位置（任意一组合法解），若不存在则输出 `IMPOSSIBLE`。

## Idea / 思路

Pair every value with its original $1$-based index, then sort by value. Use two pointers from both ends: if the current pair's sum is smaller than $x$ move the left pointer right (to increase the sum), if larger move the right pointer left, and if equal output the two original indices. Because the judge accepts **any** valid pair, we ship a problem-specific checker (`checker.cpp`) that verifies the two indices are distinct, in range, and that the corresponding values sum to $x$.

把每个值与其原始的 $1$ 起始下标绑定，再按值排序。用两端双指针：若当前两数之和小于 $x$ 就右移左指针（增大和），大于则左移右指针，相等就输出两个原始下标。由于评测接受**任意**合法解，我们提供题目专用 checker（`checker.cpp`），校验两个下标互异、在范围内、且对应值之和等于 $x$。

## Complexity / 复杂度

Sorting dominates the two-pointer sweep, so the time is $O(n \log n)$.

排序是双指针扫描的主要开销，因此时间为 $O(n \log n)$。
