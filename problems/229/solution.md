# 229 - Line Segments Trace II

## Problem / 题目
Segments span arbitrary $x$-ranges $[x_1,x_2]$ with integer slope. For each $x=0,\dots,m$, print the maximum height, or $-1$ if no segment covers $x$.

线段跨任意 $x$ 区间 $[x_1,x_2]$ 且斜率为整数。对每个 $x=0,\dots,m$，输出最大高度，若无线段覆盖则 $-1$。

## Idea / 思路
Use a Li Chao tree that supports inserting a line over a sub-range: descend to the $O(\log m)$ canonical nodes covering $[x_1,x_2]$ and run the ordinary Li Chao insertion there. A point query walks the root-to-leaf path taking the maximum line value at every node; if it stays at the sentinel, no segment covers $x$ and the answer is $-1$.

用支持「在子区间插入直线」的 Li Chao 树：下降到覆盖 $[x_1,x_2]$ 的 $O(\log m)$ 个规范结点并在那里做普通 Li Chao 插入。点查询沿根到叶路径取各结点直线值的最大；若仍为哨兵，则无线段覆盖 $x$，答案为 $-1$。

## Complexity / 复杂度
$O(n\log^2 m+m\log m)$. $O(n\log^2 m+m\log m)$。
