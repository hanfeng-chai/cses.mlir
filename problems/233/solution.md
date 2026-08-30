# 233 - Robot Path

## Problem / 题目
A robot starts at $(0,0)$ and follows axis-aligned moves, but stops immediately if it returns to any previously visited point (including points traced along earlier segments). Output the total distance moved.

机器人从 $(0,0)$ 出发执行轴对齐移动，但一旦回到任何此前访问过的点（含此前线段上经过的点）便立即停止。输出移动总距离。

## Idea / 思路
For each move (an axis-aligned segment) we need the nearest already-traced point along it. Two cases:
- **Perpendicular crossings.** Store horizontal segments in a segment tree keyed by $x$ (each adds its $y$ over its $x$-range) and vertical segments in one keyed by $y$. A move queries the path to its line and finds the nearest crossing height/abscissa in the direction of motion.
- **Collinear overlaps.** Keep, per line, a set of merged intervals; a reversal onto the previous segment is detected as an immediate (distance $0$) hit.

The minimum of both candidate distances tells where (or whether) the robot stops. Coordinates are compressed over all path points.

对每次移动（一条轴对齐线段）需要求其上最近的已走过点。两类：
- **垂直相交。** 把水平线段存入按 $x$ 建立的线段树（在其 $x$ 区间上加入其 $y$），竖直线段存入按 $y$ 建立的线段树。移动时查询到其所在直线的路径，求运动方向上最近的相交高度/横坐标。
- **共线重叠。** 对每条直线维护合并后的区间集合；折返到上一段会被识别为距离 $0$ 的即时命中。

两类候选距离的最小值决定机器人在何处（或是否）停止。坐标对所有路径点做压缩。

## Complexity / 复杂度
$O(n\log^2 n)$. $O(n\log^2 n)$。
