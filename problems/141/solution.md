# 141 - Polynomial Queries

## Problem / 题目

Maintain an array: one update adds $1,2,3,\dots$ across a range (first element $+1$, second $+2$, …), and one query sums a range.

维护数组：一种更新在区间上加 $1,2,3,\dots$（第一个 $+1$、第二个 $+2$……），一种询问区间和。

## Idea / 思路

Use a **segment tree with a lazy arithmetic-progression tag**. Each node's lazy is a pair $(\text{base}, d)$ meaning "add $\text{base} + d\cdot(\text{offset from node's left})$ to each element". A range update on a fully covered node sets $\text{base} = (\text{node left} - \text{query left} + 1)$ and $d = 1$. Tags accumulate by summing both components — importantly the common difference $d$ adds up when several progressions overlap. The contributed sum for a length-$\ell$ node is $\text{base}\cdot\ell + d\cdot\ell(\ell-1)/2$.

使用**带等差懒标记的线段树**。每个节点的懒标记是二元组 $(\text{base}, d)$，意为"给每个元素加 $\text{base} + d\cdot(\text{相对节点左端的偏移})$"。对完全覆盖的节点做区间更新时令 $\text{base} = (\text{节点左} - \text{询问左} + 1)$、$d = 1$。标记叠加时两个分量都相加——关键是当多个等差叠加时公差 $d$ 会累加。长度为 $\ell$ 的节点贡献的和为 $\text{base}\cdot\ell + d\cdot\ell(\ell-1)/2$。

## Complexity / 复杂度

Every operation is $O(\log n)$.

每个操作 $O(\log n)$。
