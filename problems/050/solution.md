# 050 - Sum of Three Values

## Problem / 题目

Find three values at distinct positions whose sum is $x$ (print any valid triple), or `IMPOSSIBLE`.

找出位于不同位置、和为 $x$ 的三个值（输出任意一组），否则输出 `IMPOSSIBLE`。

## Idea / 思路

Pair each value with its original index and sort by value. Fix the first element $a[i]$, then use two pointers on the suffix $i+1 \dots n-1$ to find a pair summing to $x - a[i]$: move the left pointer right when the sum is too small and the right pointer left when too large. Since any valid triple is accepted, a problem-specific checker (`checker.cpp`) verifies the three indices are distinct and their values sum to $x$.

把每个值与原始下标绑定并按值排序。固定第一个元素 $a[i]$，再在后缀 $i+1 \dots n-1$ 上用双指针找和为 $x - a[i]$ 的一对：和太小右移左指针，太大左移右指针。由于接受任意合法三元组，题目专用 checker（`checker.cpp`）校验三个下标互异、值之和为 $x$。

## Complexity / 复杂度

Fixing one element and two-pointering the rest is $O(n^2)$.

固定一个元素、对其余双指针，为 $O(n^2)$。
