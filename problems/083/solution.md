# 083 - Counting Rooms

## Problem / 题目

Given an $n \times m$ grid of floor (`.`) and wall (`#`) squares, count the number of rooms, where a room is a maximal set of floor squares connected horizontally or vertically.

给定一个由地板（`.`）和墙（`#`）组成的 $n \times m$ 网格，统计房间数；房间是水平或竖直相连的极大地板连通块。

## Idea / 思路

Each room is a connected component of floor cells. Scan the grid; whenever we meet an unvisited floor cell, increment the room counter and flood-fill its whole component with a BFS so it is never counted again. We use an iterative BFS (not recursion) because the grid can have up to $10^6$ cells, which would overflow the call stack.

每个房间就是一个地板连通分量。扫描网格，每遇到一个未访问的地板格，就把房间计数加一，并用 BFS 把它所在的整个连通块染色，避免重复计数。采用迭代式 BFS（而非递归），因为网格最多有 $10^6$ 个格子，递归会爆栈。

## Complexity / 复杂度

Every cell is enqueued at most once, so the time and memory are $O(nm)$.

每个格子至多入队一次，因此时间与空间均为 $O(nm)$。
