# 221 - Point in Polygon

## Problem / 题目
For each query point, report whether it is inside, outside, or on the boundary of a simple polygon.

对每个询问点，判断它在简单多边形内部、外部，还是边界上。

## Idea / 思路
First test boundary membership: the point is on the boundary if it is collinear with some edge and lies within that edge's bounding box. Otherwise use the ray-casting (crossing number) rule with an integer cross product to decide inside vs outside: count how many edges a rightward ray crosses; odd means inside.

先判边界：若点与某条边共线且落在该边包围盒内，则在边界上。否则用射线法（穿越数）配合整数叉积判断内外：统计向右射线穿过的边数，奇数为内部。

## Complexity / 复杂度
$O(nm)$ for $n$ vertices and $m$ queries. $n$ 个顶点、$m$ 个询问时 $O(nm)$。
