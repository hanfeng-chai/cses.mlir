# 096 - Round Trip II

## Problem / 题目

In a directed graph of $n$ cities and $m$ one-way flights, find a round trip (a directed cycle visiting distinct intermediate cities), or report `IMPOSSIBLE`.

在一个 $n$ 城市、$m$ 条单向航班的有向图中，找一条环游（一个经过互不相同中间城市的有向环），或报告 `IMPOSSIBLE`。

## Idea / 思路

A directed cycle exists iff a depth-first search finds a **back edge** to a node currently on the recursion stack (coloured "gray"). We DFS with three colours — white (unseen), gray (on the current path), black (finished). When an edge $u \to v$ hits a gray $v$, the cycle is $v \to \dots \to u \to v$, rebuilt by following parent pointers from $u$ up to $v$ and then reversing into forward order. The DFS is iterative to handle up to $10^5$ nodes. Any cycle is accepted, so a problem-specific checker (`checker.cpp`) validates the printed directed cycle.

有向环存在当且仅当深度优先搜索找到一条指向当前递归栈上节点（标记为"灰色"）的**返祖边**。用三色 DFS——白（未访问）、灰（在当前路径上）、黑（已完成）。当边 $u \to v$ 指向灰色 $v$ 时，环为 $v \to \dots \to u \to v$，沿父指针从 $u$ 回溯到 $v$ 再反转为正向即可重建。DFS 写成迭代式以处理多达 $10^5$ 个节点。任意环都被接受，故题目专用 checker（`checker.cpp`）校验输出的有向环。

## Complexity / 复杂度

The DFS runs in $O(n+m)$.

DFS 运行在 $O(n+m)$。
