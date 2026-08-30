# 235 - Hamming Distance

## Problem / 题目
Among $n$ bit strings of length $k\le 30$, find the minimum Hamming distance between two of them.

在 $n$ 个长度 $k\le 30$ 的二进制串中，求两个串之间的最小汉明距离。

## Idea / 思路
Pack each string into a single integer. The Hamming distance between two strings is the population count of the XOR of their integers. Compare all pairs, using the hardware popcount instruction, and keep the minimum.

把每个串压成一个整数。两个串的汉明距离即它们整数异或后的二进制 1 的个数。两两比较，用硬件 popcount 指令，取最小值。

## Complexity / 复杂度
$O(n^2)$. $O(n^2)$。
