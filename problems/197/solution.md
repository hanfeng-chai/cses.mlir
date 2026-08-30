# 197 - Word Combinations

## Problem / 题目
Given a string of length $n$ and a dictionary of $k$ words, count the number of ways to build the string by concatenating dictionary words, modulo $10^9+7$.

给定长度为 $n$ 的字符串和含 $k$ 个单词的字典，求用字典单词拼接出该字符串的方案数，模 $10^9+7$。

## Idea / 思路
Insert all dictionary words into a trie. Let $dp[i]$ be the number of ways to form the first $i$ characters, with $dp[0]=1$. From each position $i$ with $dp[i]>0$, walk the trie following $s[i],s[i+1],\dots$; whenever a terminal node is reached at length $\ell$, add $dp[i]$ to $dp[i+\ell]$. Since $n\le 5000$ the quadratic walk is fast.

把所有字典单词插入字典树。设 $dp[i]$ 为拼出前 $i$ 个字符的方案数，$dp[0]=1$。从每个 $dp[i]>0$ 的位置出发沿 $s[i],s[i+1],\dots$ 在字典树上行走，每到达一个终止结点（长度 $\ell$）就把 $dp[i]$ 加到 $dp[i+\ell]$。因 $n\le 5000$，这一平方级行走很快。

## Complexity / 复杂度
$O(n^2)$ matching plus $O(\text{total word length})$ to build the trie. 匹配 $O(n^2)$，建树 $O(\text{单词总长})$。
