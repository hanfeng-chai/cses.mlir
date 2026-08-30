# 146 - Tree Diameter

## Problem / 题目

Find the diameter of a tree: the maximum distance between any two nodes.

求树的直径：任意两节点间的最大距离。

## Idea / 思路

Use the classic two-BFS trick. Run a breadth-first search from any node and find the farthest node $u$; then run a BFS from $u$ and find the farthest node $v$. The distance between $u$ and $v$ is the diameter. (The farthest node from any start is always an endpoint of some diameter.)

使用经典的两次 BFS 技巧。从任意节点做广度优先搜索，找到最远节点 $u$；再从 $u$ 做 BFS，找到最远节点 $v$。$u$ 与 $v$ 的距离即直径。（从任意起点出发的最远节点必是某条直径的端点。）

## Complexity / 复杂度

Two BFS traversals give $O(n)$.

两次 BFS 为 $O(n)$。
