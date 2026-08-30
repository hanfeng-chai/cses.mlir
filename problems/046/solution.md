# 046 - Room Allocation

## Problem / 题目

Each customer has an arrival and departure day; two customers can share a room only if one leaves before the other arrives. Find the minimum number of rooms and a valid room assignment.

每位顾客有到达日和离开日；两位顾客只有在一个离开早于另一个到达时才能共用房间。求最少房间数以及一个合法的房间分配。

## Idea / 思路

Sort customers by arrival day. Keep a min-heap of `(departure, room)` for currently occupied rooms. For each customer, if the room that frees earliest departs before this arrival, reuse it; otherwise open a new room. The number of rooms ever opened is the minimum (it equals the maximum overlap). Because any valid assignment is accepted, we ship a checker (`checker.cpp`) verifying both that the room count is optimal and that customers sharing a room never overlap.

把顾客按到达日排序。维护一个小根堆 `(离开日, 房间号)` 表示当前占用的房间。对每位顾客，若最早空出的房间在其到达前离开，就复用它，否则开新房间。开过的房间总数就是最小值（等于最大重叠数）。由于任意合法分配都被接受，我们提供 checker（`checker.cpp`）校验房间数最优、且同房间顾客互不重叠。

## Complexity / 复杂度

Each customer does an $O(\log n)$ heap operation, so the total is $O(n \log n)$.

每位顾客做一次 $O(\log n)$ 的堆操作，总计 $O(n \log n)$。
