# 313 - Flight Route Requests

## Problem / 题目
Add the minimum number of one-way flights so that every requested route $a\to b$ becomes possible (extra reachability is allowed).

加最少的单向航线，使每个请求的路线 $a\to b$ 可达（允许产生额外可达）。

## Idea / 思路
Because extra reachability is free, each weakly-connected component of the request graph can be handled independently. A component with $N$ nodes and **no** cyclic requirement is realized by a single topological chain of $N-1$ arcs (every request goes forward in some topological order). A component that contains a non-trivial SCC (mutual-reachability requirement) needs at least one cycle, and a single big cycle through all $N$ nodes — $N$ arcs — covers every requirement. Hence the answer is

由于额外可达免费，请求图的每个弱连通分量可独立处理。含 $N$ 点且**无**环型需求的分量用一条拓扑链（$N-1$ 条弧）即可（每个请求在某拓扑序中均向前）。含非平凡 SCC（互相可达需求）的分量至少需一个环，而贯穿全部 $N$ 点的一个大环（$N$ 条弧）即可覆盖所有需求。故答案为

$$\text{answer} = n - C + C_{nt},$$

where $C$ is the number of weakly-connected components (counting isolated nodes) and $C_{nt}$ the number of components containing a non-trivial SCC. Computed with SCC condensation plus a union-find for weak components.

其中 $C$ 为弱连通分量数（含孤立点），$C_{nt}$ 为含非平凡 SCC 的分量数。用 SCC 缩点加并查集求弱连通分量实现。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
