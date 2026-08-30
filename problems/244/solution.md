# 244 - Necessary Cities

## Problem / 题目
Find all articulation points (vertices whose removal disconnects some pair of cities) in a connected undirected graph.

在连通无向图中找出所有割点（删去后会使某两城市不连通的顶点）。

## Idea / 思路
Run an iterative DFS with discovery times and low-links. A non-root vertex $u$ is an articulation point if it has a child $v$ with $\text{low}[v]\ge\text{disc}[u]$. The DFS root is an articulation point if it has more than one child in the DFS tree.

做迭代 DFS 并计算发现时间与 low 值。非根顶点 $u$ 是割点当且仅当存在子结点 $v$ 满足 $\text{low}[v]\ge\text{disc}[u]$。DFS 根是割点当且仅当其在 DFS 树中有多于一个子结点。

## Multi-solution / 多解
The cities may be printed in any order, so a custom checker compares the participant's set with the jury's set.

城市可任意顺序输出，故自定义 checker 将参赛者集合与标程集合比对。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
