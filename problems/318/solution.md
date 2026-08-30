# 318 - Split into Two Paths

## Problem / 题目
Partition all nodes of a DAG into (at most) two directed paths, or report NO.

把 DAG 的所有结点划分为（至多）两条有向路径，否则报告 NO。

## Idea / 思路
The minimum path cover of a DAG equals $n$ minus the maximum matching of its bipartite split (left = out-copy, right = in-copy, edge per DAG arc). A two-path partition exists iff this cover is $\le 2$. Use Hopcroft–Karp (with the current-arc optimization) to compute the matching; each matched arc becomes a "successor" pointer, and following pointers from the unmatched-on-the-right nodes yields the paths.

DAG 最小路径覆盖等于 $n$ 减其二分拆分（左=出副本，右=入副本，每条弧一边）的最大匹配。存在两路径划分当且仅当该覆盖 $\le 2$。用 Hopcroft–Karp（带 current-arc 优化）求匹配；每条匹配弧作为"后继"指针，从右侧未匹配点沿指针走出各路径。

## Multi-solution / 多解
Any valid two-path partition is accepted; the checker verifies the partition covers all nodes once, edges are valid, and (for NO) that the cover exceeds $2$.

任意合法两路径划分均可；checker 验证划分恰覆盖所有点、边合法，且（对 NO）覆盖数超过 $2$。

## Complexity / 复杂度
$O(E\sqrt V)$. $O(E\sqrt V)$。
