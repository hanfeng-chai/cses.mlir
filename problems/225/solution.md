# 225 - Maximum Manhattan Distances

## Problem / 题目
After each point insertion, report the maximum Manhattan distance between any two current points.

每插入一个点后，输出当前任意两点间的最大曼哈顿距离。

## Idea / 思路
Rotate coordinates to $u=x+y$ and $v=x-y$. Then the Manhattan distance equals $\max(|\Delta u|,|\Delta v|)$, so the overall maximum is $\max(\max u-\min u,\ \max v-\min v)$. Maintain the running extrema of $u$ and $v$ and answer each insertion in $O(1)$.

把坐标旋转为 $u=x+y$、$v=x-y$。曼哈顿距离等于 $\max(|\Delta u|,|\Delta v|)$，故全局最大为 $\max(\max u-\min u,\ \max v-\min v)$。维护 $u,v$ 的实时极值，每次插入 $O(1)$ 作答。

## Complexity / 复杂度
$O(n)$. $O(n)$。
