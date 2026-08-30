# 263 - Sliding Window Distinct Values

## Problem / 题目
For each window of $k$ elements, output the number of distinct values.

对每个 $k$ 元素窗口，输出其中不同值的个数.

## Idea / 思路
Compress the values and keep a frequency count over the current window. Sliding adds one element and removes one: a count rising from $0$ increases the distinct counter, a count falling to $0$ decreases it.

将值离散化并维护当前窗口的频次。滑动时加入一个、移除一个：频次从 $0$ 上升使不同值计数加一，降到 $0$ 使其减一。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
