# 219 - Line Segment Intersection

## Problem / 题目
For each query, decide whether two line segments share at least one common point.

对每个询问，判断两条线段是否至少有一个公共点。

## Idea / 思路
Use the orientation (sign of cross product) of each endpoint with respect to the other segment. The segments intersect in the general case when the two endpoints of each segment lie on opposite sides of the other. The boundary case is handled by checking, when an orientation is zero, whether the collinear endpoint lies within the other segment's bounding box.

用每个端点相对另一条线段的方向（叉积符号）。一般情形下，当每条线段的两端点位于另一条线段的两侧时相交。共线退化情形：当某方向为零时，检查该共线端点是否落在另一线段的包围盒内。

## Complexity / 复杂度
$O(1)$ per query. 每询问 $O(1)$。
