# 147 - Tree Distances I

## Problem / 题目

For each node of a tree, determine the maximum distance to any other node.

对树的每个节点，求它到任意其他节点的最大距离。

## Idea / 思路

The node farthest from any given node is always one of the two endpoints of a diameter. So find the diameter endpoints $u$ and $v$ (with the two-BFS trick), run a BFS from each to get distance arrays $d_u$ and $d_v$, and the answer for every node $i$ is $\max(d_u[i],\, d_v[i])$.

距任意节点最远的节点必是某条直径的两个端点之一。所以先求直径端点 $u$ 和 $v$（两次 BFS），从各自做一次 BFS 得到距离数组 $d_u$、$d_v$，则每个节点 $i$ 的答案为 $\max(d_u[i],\, d_v[i])$。

## Complexity / 复杂度

A constant number of BFS traversals give $O(n)$.

常数次 BFS 为 $O(n)$。
