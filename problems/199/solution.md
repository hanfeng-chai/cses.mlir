# 199 - Finding Borders

## Problem / 题目
A border is a proper prefix that is also a suffix. Print all border lengths of the string in increasing order.

边界是既是真前缀又是后缀的串。按递增顺序输出字符串所有边界的长度。

## Idea / 思路
The border lengths are exactly the values in the failure-link chain of the prefix function: $\pi(n),\ \pi(\pi(n)),\ \dots$ down to $0$. Collect them and sort.

边界长度恰好是前缀函数失配链上的值：$\pi(n),\ \pi(\pi(n)),\ \dots$ 直到 $0$。收集后排序即可。

## Complexity / 复杂度
$O(n)$. $O(n)$。
