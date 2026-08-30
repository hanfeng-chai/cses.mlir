# 152 - Counting Paths

## Problem / 题目

Given a tree and $m$ paths, compute for each node how many of the paths pass through it.

给定一棵树和 $m$ 条路径，计算每个节点被多少条路径经过。

## Idea / 思路

Use a **tree difference** technique. For a path between $a$ and $b$ with lowest common ancestor $l$, add $+1$ at $a$, $+1$ at $b$, $-1$ at $l$, and $-1$ at the parent of $l$. After all paths are marked, a single bottom-up subtree sum turns these markers into the actual count for each node (each node's value is its marker plus the sums of its children). LCAs are found with binary lifting.

使用**树上差分**。对端点为 $a$、$b$、最近公共祖先为 $l$ 的路径，在 $a$ 加 $+1$、$b$ 加 $+1$、$l$ 加 $-1$、$l$ 的父亲加 $-1$。所有路径标记完后，做一次自底向上的子树求和，就把这些标记变成每个节点的真实计数（每个节点的值为自身标记加上孩子们的和）。LCA 用二进制提升求。

## Complexity / 复杂度

With $m$ LCA queries the time is $O((n + m)\log n)$.

含 $m$ 次 LCA 查询，时间为 $O((n + m)\log n)$。
