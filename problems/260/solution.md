# 260 - Sliding Window Minimum

## Problem / 题目
For a generated array of up to $10^7$ values, output the XOR of the minimums of all windows of $k$ elements.

对生成的至多 $10^7$ 个值的数组，输出所有 $k$ 元素窗口最小值的异或。

## Idea / 思路
Use a monotonic deque of indices whose values are increasing. When a new element arrives, pop larger values from the back; drop indices that fall out of the window from the front. The front always holds the window minimum.

用单调递增的下标双端队列。新元素到来时从队尾弹出更大的值；从队首移除滑出窗口的下标。队首始终是窗口最小值。

## Complexity / 复杂度
$O(n)$. $O(n)$。
