# 310 - Tree Coin Collecting II

## Problem / 题目
Answer queries: the shortest length of a path $a\to b$ that visits **all** coin nodes.

回答询问：经过**所有**有硬币结点的最短 $a\to b$ 路径长度。

## Idea / 思路
Root the tree at a coin. Let $K$ be the minimal subtree spanning all coins (a node is in $K$ iff its subtree contains a coin); it has $C_k$ edges. For a query, the answer is $2E - \text{dist}(a,b)$ where $E$ is the edge count of the Steiner tree of the coins together with $a,b$: $E = C_k + d_K(a) + d_K(b)$ minus the overlap $\frac{d_K(a)+d_K(b)-\text{dist}(a,b)}{2}$ when $a,b$ attach to $K$ at the same point. Here $d_K(v)$ is the distance from $v$ to its entry (lowest $K$-ancestor).

以某硬币为根。设 $K$ 为覆盖所有硬币的极小子树（结点属 $K$ 当且仅当其子树含硬币），有 $C_k$ 条边。询问答案为 $2E-\text{dist}(a,b)$，$E$ 为硬币加 $a,b$ 的 Steiner 树边数：$E=C_k+d_K(a)+d_K(b)$，当 $a,b$ 在同一入口接入 $K$ 时减去重叠 $\frac{d_K(a)+d_K(b)-\text{dist}(a,b)}{2}$。$d_K(v)$ 为 $v$ 到其入口（最低 $K$ 祖先）的距离。

## Complexity / 复杂度
$O((n+q)\log n)$. $O((n+q)\log n)$。
