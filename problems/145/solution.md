# 145 - Tree Matching

## Problem / 题目

Find the maximum matching of a tree: the largest set of edges such that no node is shared by two edges.

求树的最大匹配：最大的一组边，使没有节点被两条边共用。

## Idea / 思路

Root the tree and run a DP. For each node $u$ keep two values: $d_0[u]$ = best matching in $u$'s subtree with $u$ **unmatched**, and $d_1[u]$ = best with $u$ **matched to one of its children**. Then $d_0[u] = \sum_c \max(d_0[c], d_1[c])$, and $d_1[u]$ picks one child $c$ to match with $u$: $d_1[u] = d_0[u] + \max_c\big(1 + d_0[c] - \max(d_0[c], d_1[c])\big)$. The answer is $\max(d_0[\text{root}], d_1[\text{root}])$.

把树定根并做 DP。对每个节点 $u$ 维护两个值：$d_0[u]$ = $u$ **未匹配**时子树内的最优匹配，$d_1[u]$ = $u$ **与某个孩子匹配**时的最优。则 $d_0[u] = \sum_c \max(d_0[c], d_1[c])$，而 $d_1[u]$ 选一个孩子 $c$ 与 $u$ 匹配：$d_1[u] = d_0[u] + \max_c\big(1 + d_0[c] - \max(d_0[c], d_1[c])\big)$。答案为 $\max(d_0[\text{根}], d_1[\text{根}])$。

## Complexity / 复杂度

The DP visits each node and edge once, so the time is $O(n)$.

DP 对每个节点与边各访问一次，时间为 $O(n)$。
