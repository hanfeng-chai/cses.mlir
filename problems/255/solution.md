# 255 - Dynamic Connectivity

## Problem / 题目
Edges are created and removed over time. After every event, report the number of connected components.

边随时间被创建与删除。每次事件后，报告连通分量数。

## Idea / 思路
This is offline dynamic connectivity. Each edge is active over a time interval; insert each interval into a segment tree over the time axis at its canonical nodes. A DFS of the segment tree maintains a DSU with rollback (union by rank, no path compression): apply a node's edges on entry and undo them on exit. At each leaf (a point in time) the current component count is recorded.

这是离线动态连通性。每条边在一段时间区间内有效；把每个区间插入时间轴线段树的规范结点。对线段树做 DFS，维护可回滚并查集（按秩合并、无路径压缩）：进入结点时加入其边、离开时撤销。每个叶子（某时刻）记录当前分量数。

## Complexity / 复杂度
$O((m+k)\log k\,\log n)$. $O((m+k)\log k\,\log n)$。
