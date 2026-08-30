# 238 - Reachable Nodes

## Problem / 题目
In a DAG, compute for each node the number of nodes reachable from it (including itself).

在有向无环图中，求每个结点可达的结点数（含自身）。

## Idea / 思路
Process nodes in reverse topological order. Keep a bitset of reachable nodes per node: a node's reachable set is itself unioned with the reachable sets of all its out-neighbors. The answer for each node is the population count of its bitset.

按逆拓扑序处理结点。每个结点维护一个可达结点位集：其可达集合为自身并上所有出邻居的可达集合。每个结点的答案即其位集的 1 的个数。

## Complexity / 复杂度
$O(nm/64)$. $O(nm/64)$。
