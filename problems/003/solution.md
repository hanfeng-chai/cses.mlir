# 003 - Repetitions

## Problem / 题目

Given a DNA string made of the characters `A`, `C`, `G`, `T`, we must find the length of the longest substring that consists of a single repeated character.

给定一个由字符 `A`、`C`、`G`、`T` 组成的 DNA 字符串，我们要找出仅由同一个字符重复构成的最长子串的长度。

## Idea / 思路

Scan the string once while keeping a counter of the current run of equal characters. Whenever the character matches the previous one, extend the run; otherwise reset the run to $1$. The answer is the maximum run length seen during the scan.

只需扫描字符串一次，并维护一个"当前连续相同字符段"的计数器。当当前字符与前一个相同，就把段长加一；否则把段长重置为 $1$。答案就是扫描过程中出现过的最大段长。

## Complexity / 复杂度

One linear pass: $O(n)$ time, $O(1)$ extra space, which easily handles $n$ up to $10^6$.

一次线性扫描：时间 $O(n)$，额外空间 $O(1)$，可以轻松应对 $n$ 达到 $10^6$ 的规模。
