# 306 - MST Edge Set Check

## Problem / 题目
For each query set of edges, decide whether all of them can lie in a single common MST.

对每个询问的边集，判断它们能否同时位于同一棵 MST。

## Idea / 思路
A set lies in a common MST iff, for every weight $w$, the set's weight-$w$ edges form a forest when added on top of all graph edges of weight $<w$. Process weights increasing with a **rollback union-find**: permanently add graph edges lighter than $w$, then for each query test its weight-$w$ edges with temporary unions (a repeated root means a cycle ⇒ NO), rolling back afterwards. A query is YES only if all its weight groups are independent.

边集同处一棵 MST 当且仅当对每个权 $w$，集合中权 $w$ 的边在所有权 $<w$ 的图边之上仍构成森林。用**可回滚并查集**按权升序：先永久并入比 $w$ 轻的图边，再对每个询问用临时并测其权 $w$ 边（出现同根即成环 ⇒ NO），测完回滚。询问为 YES 仅当其所有权组都独立。

## Complexity / 复杂度
$O((m+\sum|S|)\log n)$. $O((m+\sum|S|)\log n)$。
