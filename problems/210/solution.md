# 210 - Distinct Subsequences

## Problem / 题目
Count the number of distinct non-empty subsequences of a string, modulo $10^9+7$ ($n\le 5\cdot10^5$).

统计字符串不同的非空子序列个数，模 $10^9+7$（$n\le 5\cdot10^5$）。

## Idea / 思路
Let $dp[i]$ count the distinct subsequences (including the empty one) of the first $i$ characters. Each new character doubles the count, but if that character appeared before at position $j$, we subtract $dp[j-1]$ to cancel the duplicates: $dp[i]=2\,dp[i-1]-dp[\text{last}[c]-1]$. The answer is $dp[n]-1$ to exclude the empty subsequence.

设 $dp[i]$ 为前 $i$ 个字符的不同子序列数（含空串）。每个新字符使计数翻倍，但若该字符上次出现在位置 $j$，则减去 $dp[j-1]$ 以抵消重复：$dp[i]=2\,dp[i-1]-dp[\text{last}[c]-1]$。答案为 $dp[n]-1$（去掉空串）。

## Complexity / 复杂度
$O(n)$. $O(n)$。
