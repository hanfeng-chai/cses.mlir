# 154 - Path Queries

## Problem / 题目

On a rooted tree with node values, process queries: change a node's value, or sum the values on the path from the root to a node.

在有点权的有根树上处理询问：修改某节点的值，或求从根到某节点路径上的值之和。

## Idea / 思路

Take an **Euler tour** with entry/exit times. A node $u$'s value contributes to the root-path sum of exactly the nodes in $u$'s subtree, so represent it as $+\text{value}$ at $\text{tin}[u]$ and $-\text{value}$ at $\text{tout}[u]+1$ in a Fenwick tree. Then the prefix sum up to $\text{tin}[s]$ equals the sum of values on the path from the root to $s$. A value change updates the two difference positions.

取带进入/离开时间的**欧拉序**。节点 $u$ 的值恰好贡献给 $u$ 子树内所有节点的"根路径和"，故在树状数组中表示为 $\text{tin}[u]$ 处 $+\text{值}$、$\text{tout}[u]+1$ 处 $-\text{值}$。于是到 $\text{tin}[s]$ 的前缀和就等于根到 $s$ 路径上的值之和。修改值时更新这两个差分位置。

## Complexity / 复杂度

Each operation is $O(\log n)$.

每个操作 $O(\log n)$。
