# 049 - Reading Books

## Problem / 题目

Two people must each read every book from start to finish, and they cannot read the same book simultaneously. Find the minimum total time.

两个人都必须把每本书从头读到尾，且不能同时读同一本书。求最小总时间。

## Idea / 思路

The combined work is the sum of all reading times, and the two readers can overlap perfectly — finishing in that sum — unless one book is longer than all the others combined. In that bottleneck case one reader is idle while the other reads the giant book, so the answer is $\max(\text{total},\ 2 \times \text{longest})$.

总工作量是所有阅读时间之和，两个读者可以完美错峰、在该总和内读完——除非某一本书比其余所有书加起来还长。在这种瓶颈情形下，一个读者必须空等另一个读巨著，所以答案是 $\max(\text{总和},\ 2 \times \text{最长})$。

## Complexity / 复杂度

A single pass to compute the sum and maximum gives $O(n)$.

单次遍历求和与最大值即可，为 $O(n)$。
