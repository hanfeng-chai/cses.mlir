# 092 - High Score

## Problem / 题目

Walk from room $1$ to room $n$ in a directed graph where each edge changes your score by $x$ (possibly negative). Maximize the final score, or print $-1$ if it can grow without bound.

在一个有向图中从房间 $1$ 走到房间 $n$，每条边把分数改变 $x$（可正可负）。最大化最终分数，若分数可无限增长则输出 $-1$。

## Idea / 思路

This is a longest-path problem with possible positive cycles. Run Bellman–Ford for $n-1$ rounds maximizing the score reaching each room (start at $0$, others at $-\infty$). Then do one extra round: if an edge can still increase a room's score **and** that room is both reachable from $1$ and able to reach $n$, a positive cycle lies on some $1\to n$ walk, so the answer is $-1$. Otherwise the answer is the score at room $n$. Reachability is precomputed with BFS on the graph and its reverse.

这是可能含正环的最长路问题。用 Bellman–Ford 跑 $n-1$ 轮，最大化到达每个房间的分数（起点 $0$，其余 $-\infty$）。再跑一轮：若某条边仍能增加某房间的分数，**且**该房间既能从 $1$ 到达、又能到达 $n$，则某条 $1\to n$ 路径上存在正环，答案为 $-1$。否则答案为房间 $n$ 的分数。可达性用正图和反图各一次 BFS 预处理。

## Complexity / 复杂度

Bellman–Ford runs in $O(nm)$.

Bellman–Ford 运行在 $O(nm)$。
