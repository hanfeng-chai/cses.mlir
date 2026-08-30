# 157 - Finding a Centroid

## Problem / 题目

Find a centroid of a tree: a node such that, when made the root, every subtree has at most $\lfloor n/2 \rfloor$ nodes.

求树的一个重心：一个节点，作为根时每个子树至多有 $\lfloor n/2 \rfloor$ 个节点。

## Idea / 思路

Root the tree arbitrarily and compute subtree sizes. For any node $u$, removing it splits the tree into its children's subtrees (sizes $\text{size}[c]$) and the "rest" (size $n - \text{size}[u]$). A node is a centroid exactly when the largest of these components is at most $\lfloor n/2 \rfloor$. So we scan the nodes and output the first one satisfying this. Any centroid is accepted, so a problem-specific checker (`checker.cpp`) re-roots at the output node and verifies every component is small enough.

把树任意定根并算子树大小。对任意节点 $u$，删除它把树分成它孩子的子树（大小 $\text{size}[c]$）和"其余部分"（大小 $n - \text{size}[u]$）。当这些分量中最大的不超过 $\lfloor n/2 \rfloor$ 时该节点就是重心。于是扫描节点，输出第一个满足条件的。任意重心都被接受，故题目专用 checker（`checker.cpp`）以输出节点为根重算并校验每个分量足够小。

## Complexity / 复杂度

A single pass over the tree gives $O(n)$.

单次树遍历为 $O(n)$。
