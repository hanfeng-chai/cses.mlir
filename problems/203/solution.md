# 203 - All Palindromes

## Problem / 题目
For each position, output the length of the longest palindrome that ends at that position.

对每个位置，输出以该位置结尾的最长回文的长度。

## Idea / 思路
Build an eertree (palindromic tree) by inserting characters one at a time. After inserting the $i$-th character, the node `last` represents the longest palindromic *suffix* of the current prefix, so its length is exactly the answer for position $i$.

逐字符插入构建回文树（eertree）。插入第 $i$ 个字符后，结点 `last` 表示当前前缀的最长回文**后缀**，其长度恰为位置 $i$ 的答案。

## Complexity / 复杂度
$O(n)$ over a constant alphabet. 常数字母表下 $O(n)$。
