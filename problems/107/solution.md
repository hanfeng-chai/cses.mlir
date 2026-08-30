# 107 - Planets and Kingdoms

## Problem / 题目

Two planets belong to the same kingdom when each can reach the other through teleporters. Label every planet with its kingdom, printing the number of kingdoms and a label per planet.

当两颗行星彼此都能通过传送门到达对方时，它们属于同一王国。给每颗行星标注其王国，输出王国数和每颗行星的标号。

## Idea / 思路

Kingdoms are exactly the **strongly connected components** (SCCs) of the directed graph. We compute them with Kosaraju's algorithm: a first DFS records finish times, then a second DFS on the reversed graph, processed in decreasing finish order, peels off one SCC at a time. Each planet's component id (shifted to start at $1$) is a valid kingdom label. Any consistent labeling is accepted, so a problem-specific checker (`checker.cpp`) recomputes the SCCs and confirms the labeling induces the same partition.

王国恰好是有向图的**强连通分量**（SCC）。用 Kosaraju 算法求解：第一次 DFS 记录完成时间，第二次在反图上按完成时间递减处理、每次剥离一个 SCC。每颗行星的分量号（平移到从 $1$ 开始）就是合法的王国标号。任意一致的标号都被接受，故题目专用 checker（`checker.cpp`）重算 SCC 并确认标号给出相同的划分。

## Complexity / 复杂度

Both DFS passes are linear, so the time is $O(n+m)$.

两次 DFS 都是线性的，因此时间为 $O(n+m)$。
