# 261 - Sliding Window Xor

## Problem / 题目
For a generated array of up to $10^7$ values, output the XOR of the XORs of all windows of $k$ elements.

对生成的至多 $10^7$ 个值的数组，输出所有 $k$ 元素窗口异或值的异或。

## Idea / 思路
XOR is its own inverse, so the window XOR slides in $O(1)$: XOR in the entering element and XOR out the leaving one. Accumulate the XOR of every window XOR.

异或是自逆的，故窗口异或可 $O(1)$ 滑动：异或进入元素、异或离开元素。累计每个窗口异或的异或。

## Complexity / 复杂度
$O(n)$. $O(n)$。
