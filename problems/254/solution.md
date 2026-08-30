# 254 - New Roads Queries

## Problem / 题目
Roads are added one per day. For each query $(a,b)$, report the first day on which cities $a$ and $b$ become connected, or $-1$ if never.

每天新建一条道路。对每个询问 $(a,b)$，求城市 $a,b$ 首次连通的天数，若永不连通则 $-1$。

## Idea / 思路
Build a Kruskal reconstruction tree: process roads in order with a DSU, and each time two components merge create an internal node labeled with the current day whose children are the two component roots. The first day $a$ and $b$ are connected is the label of their lowest common ancestor in this tree (or $-1$ if they lie in different trees), answered with binary-lifting LCA.

构建 Kruskal 重构树：按顺序用并查集处理道路，每次两个分量合并就新建一个以当前天数为标号的内部结点，其孩子为两分量的根。$a,b$ 首次连通的天数即它们在该树中最近公共祖先的标号（若在不同树则 $-1$），用倍增 LCA 回答。

## Complexity / 复杂度
$O((n+m+q)\log n)$. $O((n+m+q)\log n)$。
