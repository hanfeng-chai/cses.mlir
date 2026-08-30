# 241 - Substring Reversals

## Problem / 题目
Process operations that reverse a substring $[a,b]$. Output the final string.

处理「反转子串 $[a,b]$」的操作。输出最终字符串。

## Idea / 思路
Use an implicit treap with a lazy reversal flag. To reverse $[a,b]$, split out the middle part, toggle its reversal flag, and merge back. The flag is pushed down (swapping children) during split, merge, and the final traversal.

用带懒惰反转标记的隐式 treap。反转 $[a,b]$：分裂出中间段、翻转其反转标记、再合并回去。该标记在 split、merge 和最终遍历时下推（交换左右子树）。

## Complexity / 复杂度
$O((n+m)\log n)$. $O((n+m)\log n)$。
