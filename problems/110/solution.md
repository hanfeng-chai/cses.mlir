# 110 - Mail Delivery

## Problem / 题目

Find a route that starts and ends at the post office (crossing $1$) and traverses every street exactly once, or report `IMPOSSIBLE`.

找一条从邮局（路口 $1$）出发并返回、且每条街道恰好走一次的路线，或报告 `IMPOSSIBLE`。

## Idea / 思路

Such a route is an **Eulerian circuit**. It exists iff every crossing has even degree and all streets lie in one connected component. We build adjacency lists with edge ids and run Hierholzer's algorithm iteratively: walk forward consuming unused edges, and whenever a vertex has no unused edge, append it to the circuit and back up. If the resulting circuit uses all $m$ streets (length $m+1$) it is valid; otherwise the graph is disconnected. Any valid Euler circuit is accepted, so a problem-specific checker (`checker.cpp`) verifies it starts/ends at $1$ and uses each street once.

这种路线是**欧拉回路**。它存在当且仅当每个路口度数为偶且所有街道在一个连通分量内。我们用带边号的邻接表，迭代运行 Hierholzer 算法：向前走消耗未用边，当某点无未用边时把它加入回路并回退。若得到的回路用满全部 $m$ 条街道（长度 $m+1$）则合法；否则图不连通。任意合法欧拉回路都被接受，故题目专用 checker（`checker.cpp`）校验它起止于 $1$ 且每条街道用一次。

## Complexity / 复杂度

Hierholzer's algorithm runs in $O(n+m)$.

Hierholzer 算法运行在 $O(n+m)$。
