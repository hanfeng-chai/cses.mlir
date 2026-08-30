# 227 - Intersection Points

## Problem / 题目
Count the intersection points of $n$ horizontal and vertical segments (no parallel overlaps, no endpoint intersections).

统计 $n$ 条水平与竖直线段的交点数（无平行重叠，端点不为交点）。

## Idea / 思路
Sweep along the $x$-axis. A horizontal segment is "active" between its left and right $x$ events; insert/remove its $y$ into a Fenwick tree over $y$. When reaching a vertical segment at $x$ spanning $[y_1,y_2]$, the number of active horizontal segments with $y\in[y_1,y_2]$ is a range query, which counts its crossings.

沿 $x$ 轴扫描。水平线段在其左右 $x$ 事件间「激活」，把其 $y$ 插入/删除到树状数组（按 $y$）。遇到 $x$ 处、跨 $[y_1,y_2]$ 的竖直线段时，$y\in[y_1,y_2]$ 内激活的水平线段数即一次区间查询，对应其交点数。

## Complexity / 复杂度
$O(n\log n)$. $O(n\log n)$。
