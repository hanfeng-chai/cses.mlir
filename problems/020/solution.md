# 020 - Knight Moves Grid

## Problem / 题目

On an $n \times n$ board, output for every square the minimum number of knight moves needed to reach it starting from the top-left corner.

在 $n \times n$ 的棋盘上，对每个格子输出从左上角出发、用骑士（马）走到该格所需的最少步数。

## Idea / 思路

This is a single-source shortest-path problem on an unweighted graph, so we run a **breadth-first search** from $(0,0)$. Each cell can move to up to eight knight destinations; the BFS distance label of a cell is its minimum number of moves. We fill a distance grid during the BFS and print it.

这是无权图上的单源最短路问题，所以从 $(0,0)$ 跑一次**广度优先搜索（BFS）**。每个格子可走到至多八个马步目标；BFS 给某格的距离标号就是它的最少步数。BFS 过程中填好距离网格再输出。

## Complexity / 复杂度

Each of the $n^2$ cells is enqueued once and relaxes eight neighbours, so the time is $O(n^2)$.

$n^2$ 个格子每个只入队一次、各松弛八个邻居，因此时间为 $O(n^2)$。
