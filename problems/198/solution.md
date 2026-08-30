# 198 - String Matching

## Problem / 题目
Count the number of positions where a pattern of length $m$ occurs in a string of length $n$ ($n,m\le 10^6$).

统计长度为 $m$ 的模式串在长度为 $n$ 的文本串中出现的位置数（$n,m\le 10^6$）。

## Idea / 思路
Build the KMP prefix function of the pattern and scan the text once, advancing the matched length and falling back along the failure links on mismatches. Each time the matched length reaches $m$, increment the counter and follow the failure link to continue.

构造模式串的 KMP 前缀函数，对文本扫描一遍，用失配指针在不匹配时回退、匹配时前进。每当匹配长度达到 $m$ 就计数加一并沿失配指针继续。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
