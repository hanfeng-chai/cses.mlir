# 015 - Creating Strings

## Problem / 题目

Given a string, print the number of its distinct permutations and then all of them in alphabetical order.

给定一个字符串，输出它所有不同排列的数量，然后按字母序输出全部排列。

## Idea / 思路

Sort the string first, then repeatedly call `next_permutation`. This standard library function generates permutations in lexicographic order and, crucially, **skips duplicates automatically** when characters repeat, so we simply collect every permutation it yields until it wraps around.

先把字符串排序，然后反复调用 `next_permutation`。这个标准库函数按字典序生成排列，而且在有重复字符时会**自动跳过重复排列**，所以我们只需收集它产生的每个排列，直到回到起点为止。

## Complexity / 复杂度

If there are $P$ distinct permutations of a length-$n$ string, the work is $O(P \cdot n)$; since $n \le 8$ this is tiny.

设长度为 $n$ 的字符串有 $P$ 个不同排列，则工作量为 $O(P \cdot n)$；由于 $n \le 8$，规模很小。
