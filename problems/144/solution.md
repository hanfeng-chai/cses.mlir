# 144 - Subordinates

## Problem / 题目

In a company tree rooted at employee $1$, compute for each employee the number of their subordinates (the size of their subtree minus one).

在以员工 $1$ 为根的公司树中，计算每个员工的下属人数（其子树大小减一）。

## Idea / 思路

Compute subtree sizes with one tree traversal. Using an iterative DFS we obtain a pre-order; processing nodes in reverse pre-order (children before parents) lets us set $\text{size}[u] = 1 + \sum_{\text{child } c} \text{size}[c]$. The number of subordinates of $u$ is $\text{size}[u] - 1$.

用一次树遍历计算子树大小。用迭代 DFS 得到前序；按前序逆序处理（孩子先于父亲）即可令 $\text{size}[u] = 1 + \sum_{\text{孩子 } c} \text{size}[c]$。$u$ 的下属数为 $\text{size}[u] - 1$。

## Complexity / 复杂度

A single traversal gives $O(n)$.

单次遍历为 $O(n)$。
