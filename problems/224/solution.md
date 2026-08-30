# 224 - Convex Hull

## Problem / 题目
Output all points that lie on the convex hull of $n$ points (vertices and points on hull edges), in any order.

输出 $n$ 个点的凸包上的所有点（顶点以及落在凸包边上的点），顺序任意。

## Idea / 思路
Use Andrew's monotone chain after sorting the points. To keep collinear points that lie on hull edges, pop a vertex only on a strict right turn (cross product $<0$), retaining points with zero cross product. The lower and upper chains together give every boundary point; deduplicate the result.

排序后用 Andrew 单调链。为保留落在凸包边上的共线点，仅在严格右转（叉积 $<0$）时弹出顶点，保留叉积为零的点。下、上链合并即得全部边界点；去重后输出。

## Multi-solution / 多解
The point set is unique but any order is accepted, so a custom checker independently computes the boundary set (strict hull plus $O(\log n)$ point location) and compares it as a set.

点集唯一但顺序任意，故自定义 checker 用独立方法（严格凸包 + $O(\log n)$ 点定位）计算边界集合并按集合比较。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
