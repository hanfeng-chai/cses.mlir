# 038 - Towers

## Problem / 题目

Process cubes in the given order. Each cube may go on top of a tower whose current top is strictly larger, or start a new tower. Minimise the number of towers.

按给定顺序处理立方体。每个立方体可放在塔顶严格更大的塔上，或新建一座塔。求最少塔数。

## Idea / 思路

Maintain the multiset of tower tops. For each cube, find the smallest top strictly greater than it with `upper_bound`; place the cube there, so that top becomes the cube's size. If no such top exists, the cube must start a new tower. The number of tops at the end is the minimum number of towers — this is the patience-sorting greedy.

维护各塔顶的 multiset。对每个立方体，用 `upper_bound` 找到严格大于它的最小塔顶，把它放上去，使该塔顶变为该立方体的大小。若不存在这样的塔顶，则必须新建一座塔。最终塔顶的个数就是最少塔数——这就是 patience sorting 贪心。

## Complexity / 复杂度

Each cube does an $O(\log n)$ multiset operation, so the total is $O(n \log n)$.

每个立方体做一次 $O(\log n)$ 的 multiset 操作，总计 $O(n \log n)$。
