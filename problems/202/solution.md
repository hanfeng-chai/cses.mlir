# 202 - Longest Palindrome

## Problem / 题目
Find a longest palindromic substring of the given string ($n\le 10^6$). Any longest one is accepted.

求给定字符串的一个最长回文子串（$n\le 10^6$）。任意一个最长解均可。

## Idea / 思路
Run Manacher's algorithm on the string padded with separators (`^#a#b#...#$`). It computes, for every center, the radius of the longest palindrome there in linear time. Take the center with the maximum radius and output the corresponding substring.

在用分隔符填充的串（`^#a#b#...#$`）上运行 Manacher 算法，线性时间求出每个中心处最长回文的半径。取半径最大的中心，输出对应子串。

## Multi-solution / 多解
Several longest palindromes may exist, so a custom checker verifies the output is a palindrome, occurs in the string, and has length equal to the true maximum.

最长回文可能不唯一，故自定义 checker 验证输出是回文、出现在串中、且长度等于真实最大值。

## Complexity / 复杂度
$O(n)$. $O(n)$。
