# 155 - Path Queries II

## Problem / 题目

On a tree with node values, process queries: change a node's value, or find the maximum value on the path between two nodes.

在有点权的树上处理询问：修改某节点的值，或求两节点间路径上的最大值。

## Idea / 思路

Use **Heavy-Light Decomposition (HLD)**. Split the tree into heavy chains so that any root-to-node path crosses only $O(\log n)$ chains; lay the chains contiguously in a base array and build a max segment tree over it. A value update is a point update at the node's position. A path-max query walks up the two endpoints chain by chain — always lifting the endpoint whose chain head is deeper — querying the segment tree on each chain segment, until both lie on the same chain.

使用**树链剖分（HLD）**。把树拆成重链，使任意根到节点的路径只穿过 $O(\log n)$ 条链；把链连续地排进基础数组并在其上建最大值线段树。修改值是节点位置处的单点更新。路径最大值查询让两端点逐链上行——每次提升链头更深的那端——在每段链上查询线段树，直到两端落在同一条链上。

## Complexity / 复杂度

Each query touches $O(\log n)$ chains with an $O(\log n)$ segment query each, giving $O(\log^2 n)$.

每个查询涉及 $O(\log n)$ 条链、每条一次 $O(\log n)$ 段查询，为 $O(\log^2 n)$。
