# 350 - Nearest Campsites II

## Problem / 题目

Same setup as problem 349, but print the distance from **each** free campsite to its nearest reserved campsite (in input order), instead of just the maximum.

设定与第 349 题相同，但要按输入顺序输出**每个**空闲营地到最近已预订营地的距离，而不是只求最大值。

## Idea / 思路

Identical solution to 349 — the same bounding-box-pruned $k$-d tree built once over the reserved campsites — except every query result is printed instead of only tracking the running maximum. See [349](../349/solution.md) for the full explanation of the search technique.

解法与第 349 题完全相同——对已预订营地建一次带包围盒剪枝的 k-d 树——只是把每次查询结果都输出，而不是只跟踪运行中的最大值。搜索技巧的完整说明见 [349](../349/solution.md)。

## Complexity / 复杂度

$O((n+m)\log n)$, same as problem 349.

$O((n+m)\log n)$，与第 349 题相同。
