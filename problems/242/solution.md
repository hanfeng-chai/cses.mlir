# 242 - Reversals and Sums

## Problem / 题目
Process two operations on an array: reverse a subarray, and compute the sum of a subarray.

对数组处理两类操作：反转子数组，求子数组之和。

## Idea / 思路
Use an implicit treap that stores a subtree sum and a lazy reversal flag in each node. A reversal splits out the range, toggles its flag, and merges back; a sum query splits out the range and reads the stored subtree sum. The sum is unaffected by reversal, so both operations run in logarithmic time.

用隐式 treap，每个结点维护子树和与懒惰反转标记。反转操作分裂出区间、翻转标记、再合并；求和操作分裂出区间并读取其子树和。和不受反转影响，故两类操作均为对数时间。

## Complexity / 复杂度
$O((n+m)\log n)$. $O((n+m)\log n)$。
