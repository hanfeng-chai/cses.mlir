# 201 - Minimal Rotation

## Problem / 题目
Output the lexicographically smallest rotation of a string of length $n$ ($n\le 10^6$).

输出长度为 $n$ 的字符串的字典序最小旋转（$n\le 10^6$）。

## Idea / 思路
Booth's algorithm finds the starting index of the least rotation in linear time by maintaining a candidate start $k$ and a failure array over the doubled string, shifting $k$ whenever a smaller continuation is found. Output the rotation beginning at that index.

Booth 算法在线性时间内求出最小旋转的起点：在「串自身拼接两遍」上维护候选起点 $k$ 与失配数组，一旦发现更小的延续就移动 $k$。最后输出从该起点开始的旋转。

## Complexity / 复杂度
$O(n)$. $O(n)$。
