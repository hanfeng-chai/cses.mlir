# 319 - Network Renovation

## Problem / 题目
Add the minimum number of edges to a tree so it becomes 2-edge-connected (no bridges).

给树加最少的边使其 2-边连通（无桥）。

## Idea / 思路
With $L$ leaves the answer is $\lceil L/2 \rceil$. List the leaves in DFS order around the tree and connect leaf $i$ with leaf $(i + \lfloor L/2 \rfloor) \bmod L$. These "diameter" chords ensure every tree edge is covered by some new cycle, so no bridge remains.

设叶子数 $L$，答案为 $\lceil L/2 \rceil$。按 DFS 序环绕列出叶子，连接叶 $i$ 与叶 $(i+\lfloor L/2\rfloor)\bmod L$。这些"直径"弦使每条树边都被某个新环覆盖，从而无桥。

## Multi-solution / 多解
Any valid minimal augmentation is accepted; the checker verifies the count equals $\lceil L/2\rceil$ and the augmented graph is bridgeless.

任意合法的最小加边方案均可；checker 验证数量等于 $\lceil L/2\rceil$ 且加边后无桥。

## Complexity / 复杂度
$O(n)$. $O(n)$。
