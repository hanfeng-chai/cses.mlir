# 042 - Josephus Problem I

## Problem / 题目

$n$ children stand in a circle. Repeatedly skip one child and remove the next, until none remain. Output the order of removal.

$n$ 个孩子站成一圈。反复跳过一个、移除下一个，直到无人剩下。输出移除顺序。

## Idea / 思路

Simulate with a queue holding the children in circular order. Each step moves the front child to the back (the skipped one) and then removes the new front (the eliminated one, which we output). Each operation is $O(1)$.

用队列按环形顺序存放孩子来模拟。每一步把队首孩子移到队尾（被跳过的那个），然后移除新的队首（被淘汰的那个，输出它）。每次操作 $O(1)$。

## Complexity / 复杂度

Each child is skipped and removed a constant number of times, so the total is $O(n)$.

每个孩子被跳过与移除常数次，因此总计 $O(n)$。
