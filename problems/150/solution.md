# 150 - Company Queries II

## Problem / 题目

In a company hierarchy (a rooted tree), answer queries for the lowest common ancestor (lowest common boss) of two employees.

在公司层级（有根树）中回答询问：两个员工的最近公共祖先（最近公共老板）。

## Idea / 思路

Use **binary lifting** for LCA. Precompute each node's depth and the ancestor tables $up[j]$. For a query $(a,b)$, first lift the deeper node up to the same depth as the other, then lift both simultaneously by decreasing powers of two while their ancestors differ; the LCA is the parent of where they stop.

用**二进制提升**求 LCA。预处理每个节点的深度和祖先表 $up[j]$。对询问 $(a,b)$，先把较深的节点提升到与另一个同深度，再以递减的 $2$ 的幂同时提升两者（当它们的祖先不同时），LCA 即它们停下处的父亲。

## Complexity / 复杂度

Preprocessing is $O(n\log n)$ and each query is $O(\log n)$.

预处理 $O(n\log n)$，每个询问 $O(\log n)$。
