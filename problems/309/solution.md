# 309 - Tree Coin Collecting I

## Problem / 题目
Answer queries: the shortest length of a path $a\to b$ that visits at least one coin node.

回答询问：经过至少一个有硬币结点的最短 $a\to b$ 路径长度。

## Idea / 思路
Let $g(v)$ be the distance from $v$ to the nearest coin (a multi-source BFS from all coins). The answer is $\text{dist}(a,b) + 2\cdot\min_{v\in P(a,b)} g(v)$, where $P(a,b)$ is the tree path: you detour from the path to the closest coin and back. Path distance and the minimum of $g$ along the path are computed with binary-lifting LCA.

设 $g(v)$ 为 $v$ 到最近硬币的距离（从所有硬币的多源 BFS）。答案为 $\text{dist}(a,b)+2\cdot\min_{v\in P(a,b)} g(v)$，$P(a,b)$ 为树上路径：从路径绕到最近硬币再返回。路径距离与路径上 $g$ 的最小值用倍增 LCA 求。

## Complexity / 复杂度
$O((n+q)\log n)$. $O((n+q)\log n)$。
