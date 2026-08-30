# 239 - Reachability Queries

## Problem / 题目
In a directed graph, answer queries of the form "is node $b$ reachable from node $a$?"

在有向图中，回答「能否从 $a$ 到达 $b$」的询问。

## Idea / 思路
Condense the graph into strongly connected components (SCCs) with Tarjan's algorithm, giving a DAG. Compute, for each SCC in reverse topological order, a bitset of reachable SCCs (itself plus its successors). A query reduces to checking whether the SCC of $b$ is in the reachable set of the SCC of $a$.

用 Tarjan 算法把图缩成强连通分量（SCC），得到 DAG。对每个 SCC 按逆拓扑序计算可达 SCC 的位集（自身加后继）。询问归结为检查 $b$ 所在 SCC 是否在 $a$ 所在 SCC 的可达集合中。

## Complexity / 复杂度
$O(nm/64 + q)$. $O(nm/64 + q)$。
