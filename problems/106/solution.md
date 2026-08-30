# 106 - Flight Routes Check

## Problem / 题目

Determine whether a directed graph of $n$ cities and $m$ flights is strongly connected (every city reaches every other). If not, also output two cities $a, b$ with no route from $a$ to $b$.

判断一个 $n$ 城市、$m$ 航班的有向图是否强连通（任意城市可达任意城市）。若否，再输出两座没有 $a$ 到 $b$ 路线的城市 $a, b$。

## Idea / 思路

A directed graph is strongly connected iff, from any fixed city (say city $1$), every city is reachable **and** city $1$ is reachable from every city. The second condition is checked on the reversed graph. Run one BFS on the original graph and one on the reverse, both from city $1$. If some city is unreachable in the forward search, $(1, x)$ is a witness; if some city cannot reach $1$ (unreachable in the reverse search), $(x, 1)$ is a witness; otherwise the graph is strongly connected. Any valid witness pair is accepted, so a problem-specific checker (`checker.cpp`) confirms that $b$ is truly unreachable from $a$.

有向图强连通当且仅当从任一固定城市（如城市 $1$）出发每座城市都可达，**且**每座城市都能到达城市 $1$。后者在反图上检验。在原图和反图上各从城市 $1$ 跑一次 BFS。若正向搜索中某城不可达，则 $(1, x)$ 是反例；若某城在反向搜索中不可达（即到不了 $1$），则 $(x, 1)$ 是反例；否则图强连通。任意合法反例对都被接受，故题目专用 checker（`checker.cpp`）确认 $b$ 确实从 $a$ 不可达。

## Complexity / 复杂度

Two BFS traversals run in $O(n+m)$.

两次 BFS 遍历运行在 $O(n+m)$。
