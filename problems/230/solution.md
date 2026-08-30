# 230 - Lines and Queries I

## Problem / 题目
Process queries online: add a line $ax+b$, or ask the maximum value of any line at a position $x$.

在线处理询问：加入直线 $ax+b$，或询问位置 $x$ 处所有直线的最大值。

## Idea / 思路
Maintain a Li Chao tree over the query domain $x\in[0,10^5]$. Adding a line is an insertion; a query takes the maximum value along the root-to-leaf path. The structure supports interleaved inserts and queries directly.

在查询域 $x\in[0,10^5]$ 上维护 Li Chao 树。加入直线即插入；查询取根到叶路径上的最大值。该结构天然支持插入与查询交替进行。

## Complexity / 复杂度
$O(n\log X)$. $O(n\log X)$。
