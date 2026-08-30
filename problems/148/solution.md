# 148 - Tree Distances II

## Problem / 题目

For each node of a tree, compute the sum of distances from that node to all other nodes.

对树的每个节点，计算它到所有其他节点的距离之和。

## Idea / 思路

Use **rerooting DP**. Root the tree and first compute, bottom-up, $\text{size}[u]$ and $\text{down}[u]$ = sum of distances from $u$ to nodes in its subtree, via $\text{down}[u] = \sum_c (\text{down}[c] + \text{size}[c])$. The answer for the root is $\text{down}[\text{root}]$. Then push the answer down: moving the root from $u$ to a child $v$, the $\text{size}[v]$ nodes get one closer and the other $n - \text{size}[v]$ get one farther, so $\text{ans}[v] = \text{ans}[u] - \text{size}[v] + (n - \text{size}[v])$.

使用**换根 DP**。把树定根，先自底向上算 $\text{size}[u]$ 和 $\text{down}[u]$ = $u$ 到其子树内节点的距离和，$\text{down}[u] = \sum_c (\text{down}[c] + \text{size}[c])$。根的答案为 $\text{down}[\text{根}]$。再自顶向下推：把根从 $u$ 移到孩子 $v$ 时，$\text{size}[v]$ 个节点近了一步、另外 $n - \text{size}[v]$ 个远了一步，故 $\text{ans}[v] = \text{ans}[u] - \text{size}[v] + (n - \text{size}[v])$。

## Complexity / 复杂度

Two passes over the tree give $O(n)$.

两遍树遍历为 $O(n)$。
