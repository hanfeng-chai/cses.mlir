# 232 - Area of Rectangles

## Problem / 题目
Compute the total area of the union of $n$ axis-aligned rectangles.

求 $n$ 个轴对齐矩形并集的总面积。

## Idea / 思路
Sweep a vertical line across the $x$-axis. Each rectangle contributes a $+1$ event at its left edge and a $-1$ event at its right edge over its $y$-interval. A segment tree over compressed $y$-coordinates maintains the total covered $y$-length under the current set of active intervals; multiplying that length by the gap between consecutive event $x$-coordinates and summing gives the union area.

用竖直扫描线沿 $x$ 轴移动。每个矩形在其左边界贡献 $+1$、右边界贡献 $-1$ 事件（作用于其 $y$ 区间）。在压缩 $y$ 坐标上的线段树维护当前激活区间所覆盖的 $y$ 总长度；该长度乘以相邻事件 $x$ 之差并累加，即得并集面积。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
