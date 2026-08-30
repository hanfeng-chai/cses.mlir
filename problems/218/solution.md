# 218 - Point Location Test

## Problem / 题目
For each query, decide whether point $p_3$ is to the left, to the right, or on the line through $p_1\to p_2$.

对每个询问，判断点 $p_3$ 在有向直线 $p_1\to p_2$ 的左侧、右侧，还是线上。

## Idea / 思路
Compute the cross product $(p_2-p_1)\times(p_3-p_1)$. A positive value means left, negative means right, and zero means the point is on the line. Coordinates up to $10^9$ keep the cross product within 64-bit range.

计算叉积 $(p_2-p_1)\times(p_3-p_1)$。正为左侧，负为右侧，零为线上。坐标至 $10^9$ 时叉积仍在 64 位范围内。

## Complexity / 复杂度
$O(1)$ per query. 每询问 $O(1)$。
