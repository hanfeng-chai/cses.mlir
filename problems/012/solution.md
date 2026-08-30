# 012 - Palindrome Reorder

## Problem / 题目

Given a string of uppercase letters, rearrange its characters into a palindrome, or report that it is impossible.

给定一个由大写字母组成的字符串，把它的字符重排成一个回文串，或报告无法做到。

## Idea / 思路

A multiset of letters can form a palindrome **iff at most one letter has an odd count** (that letter, if any, must sit in the middle). Count every letter; if two or more have odd counts, print `NO SOLUTION`. Otherwise build the first half by taking $\lfloor cnt/2 \rfloor$ copies of each letter in alphabetical order, place the single odd letter (if it exists) in the center, then append the reverse of the first half. Since the judge accepts **any** valid palindrome, we ship a problem-specific testlib checker (`checker.cpp`) that verifies the output is a palindrome using exactly the given multiset of letters.

一组字母能重排成回文，**当且仅当至多一个字母出现奇数次**（这个字母若存在必须放在正中间）。统计每个字母的个数；若有两个及以上字母为奇数次，输出 `NO SOLUTION`。否则按字母序各取 $\lfloor cnt/2 \rfloor$ 个拼出前半段，把那个唯一的奇数字母（若有）放中间，再接上前半段的逆序。由于评测接受**任意**合法回文，我们提供题目专用的 testlib checker（`checker.cpp`），校验输出确实是回文且恰好用到给定的字母多重集。

## Complexity / 复杂度

Counting and constructing each take linear time, so the algorithm runs in $O(n + 26)$.

统计和构造都是线性的，因此算法运行在 $O(n + 26)$。
