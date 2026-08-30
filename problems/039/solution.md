# 039 - Traffic Lights

## Problem / 题目

A street of length $x$ gets $n$ traffic lights added one by one. After each addition, report the length of the longest passage with no lights.

长度为 $x$ 的街道上逐个添加 $n$ 盏红绿灯。每次添加后，报告没有灯的最长路段长度。

## Idea / 思路

Keep the light positions in an ordered `set` (including the two ends $0$ and $x$) and the current segment lengths in a `multiset`. Adding a light $p$ falls between its neighbours $lo$ and $hi$ in the set; it splits that segment, so we remove the length $hi-lo$ and insert $p-lo$ and $hi-p$. The answer after each step is the largest value in the multiset.

把灯的位置放进有序 `set`（含两端 $0$ 与 $x$），把当前各段长度放进 `multiset`。添加灯 $p$ 时，它落在 set 中邻居 $lo$ 与 $hi$ 之间，分裂该段：删除长度 $hi-lo$，插入 $p-lo$ 与 $hi-p$。每步的答案就是 multiset 中的最大值。

## Complexity / 复杂度

Each addition does $O(\log n)$ set/multiset operations, so the total is $O(n \log n)$.

每次添加做 $O(\log n)$ 的 set/multiset 操作，总计 $O(n \log n)$。
