# 212 - String Functions

## Problem / 题目
Output the Z-function (with $z(1)=0$) and the prefix function $\pi$ of a string ($n\le 10^6$).

输出字符串的 Z 函数（约定 $z(1)=0$）和前缀函数 $\pi$（$n\le 10^6$）。

## Idea / 思路
The Z-function is computed with the standard Z-algorithm maintaining the rightmost matched segment $[l,r]$; the problem defines $z(1)=0$, so set the first value to $0$. The prefix function $\pi$ is the usual KMP failure function, the longest proper prefix that is also a suffix of each prefix.

Z 函数用标准 Z 算法计算，维护最靠右的匹配段 $[l,r]$；题目约定 $z(1)=0$，故首项置 $0$。前缀函数 $\pi$ 即常规 KMP 失配函数，是每个前缀的最长「既是真前缀又是后缀」的长度。

## Complexity / 复杂度
$O(n)$. $O(n)$。
