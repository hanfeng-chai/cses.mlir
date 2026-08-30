# 245 - Eulerian Subgraphs

## Problem / 题目
Count the spanning subgraphs (all nodes, some edges) in which every node has even degree, modulo $10^9+7$.

统计每个结点度数都为偶数的生成子图（保留全部结点、部分边）个数，模 $10^9+7$。

## Idea / 思路
The even-degree subgraphs form the cycle space of the graph, a vector space over $\mathbb{F}_2$ whose dimension is the cyclomatic number $m-n+c$, where $c$ is the number of connected components. Hence the answer is $2^{m-n+c}$, computed with a DSU to count components.

偶度子图构成图的环空间，是 $\mathbb{F}_2$ 上的向量空间，维数为圈秩 $m-n+c$，其中 $c$ 为连通分量数。故答案为 $2^{m-n+c}$，用并查集统计分量数即可。

## Complexity / 复杂度
$O((n+m)\,\alpha)$. $O((n+m)\,\alpha)$。
