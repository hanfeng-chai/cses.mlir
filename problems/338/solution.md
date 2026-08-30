# 338 - Tournament Graph Distribution

## Problem / 题目

A *tournament* on $n$ labeled nodes is a complete graph with each edge given one direction. For each $k=1,\dots,n$, count the tournaments on $n$ nodes with exactly $k$ strongly connected components, modulo $10^9+7$.

$n$ 个带标号点上的"锦标赛图"是完全图的每条边都定向后的结果。对每个 $k=1,\dots,n$，求恰好有 $k$ 个强连通分量的 $n$ 点锦标赛图个数，对 $10^9+7$ 取模。

## Idea / 思路

**Key structural fact.** In *any* tournament, if you contract each strongly connected component (SCC) to a single node, the resulting "condensation" graph is itself a tournament on the SCCs, and it must be acyclic (else the cycle's SCCs would merge into one bigger SCC) — and an acyclic tournament is always **totally ordered** (transitive): $S_1\to S_2\to\dots\to S_k$, with literally *every* edge between two different SCCs $S_a,S_b$ ($a<b$) pointing from $S_a$ to $S_b$ (if even one edge went the "wrong" way, combined with the strong connectivity inside $S_a$ and $S_b$, it would create a cycle joining them into one SCC — contradiction). So counting tournaments with exactly $k$ SCCs is the same as counting **ordered set partitions** of the $n$ labeled nodes into $k$ nonempty groups $G_1,\dots,G_k$, where each $G_i$ *internally* forms a strongly connected tournament, and *all* cross-group edges are forced by the ordering.

**Step 1 — count strongly connected tournaments $s(m)$ on $m$ labeled nodes.** Every tournament on $m$ nodes has a well-defined "first" SCC (the source of its total order) of some size $t$; the remaining $m-t$ nodes form an *arbitrary, unconstrained* tournament (since once the first SCC is fixed, what happens further down the order can be anything). Counting all $2^{\binom m2}$ tournaments on $m$ nodes by the size $t$ of this first SCC gives
$$T(m)=\sum_{t=1}^{m}\binom{m}{t}\,s(t)\,T(m-t),\qquad T(m)=2^{\binom m2}\ (\text{total tournaments on } m \text{ nodes}),$$
so, isolating the $t=m$ term (which is just $s(m)$ itself, since then $T(0)=1$):
$$s(m)=T(m)-\sum_{t=1}^{m-1}\binom{m}{t}\,s(t)\,T(m-t).$$
This is computed for $m=1,\dots,n$ with an $O(n^2)$ DP.

**Step 2 — assemble $k$ groups via an exponential generating function (EGF).** Let $G(x)=\sum_{m\ge1}\dfrac{s(m)}{m!}x^m$. The number of ways to partition $n$ *labeled* nodes into an ordered sequence of $k$ nonempty groups, each internally counted by $s(\cdot)$, is the standard EGF composition rule:
$$f(n,k)=n!\cdot[x^n]\,G(x)^k.$$
The implementation keeps `cur` = coefficients of $G(x)^j$ (starting at $j=1$ and repeatedly multiplying by $G$), reading off $f(n,j)=n!\cdot\text{cur}[n]$ at each step.

*Sanity check ($n=3$):* $s(1)=1,\ s(2)=0,\ s(3)=2$ (only the two rotations of a 3-cycle are strongly connected among the $8$ tournaments on 3 nodes), so $G=x+\tfrac13x^3+\dots$. Then $f(3,1)=6\cdot\tfrac13=2$, $f(3,2)=6\cdot[x^3](x+\tfrac13x^3)^2=6\cdot0=0$ (degree-3 term of the square only comes from $x\cdot x\cdot x$-type combinations that don't fit two factors), $f(3,3)=6\cdot[x^3]x^3=6$ — giving $2,0,6$, exactly the sample output.

**关键结构事实。** 在**任意**锦标赛图中，把每个强连通分量（SCC）缩成一个点后得到的"缩点图"本身也是一个锦标赛图，并且它必须无环（否则环上的 SCC 会合并成一个更大的 SCC）——而无环的锦标赛图必然是**全序**的（传递的）：$S_1\to S_2\to\dots\to S_k$，并且两个不同 SCC $S_a,S_b$（$a<b$）之间**所有**边都从 $S_a$ 指向 $S_b$（哪怕只有一条边"反向"，结合 $S_a$、$S_b$ 内部的强连通性，就会形成一个把它们并成一个 SCC 的环——矛盾）。所以数恰有 $k$ 个 SCC 的锦标赛图，等价于数把 $n$ 个带标号点划分成 $k$ 个非空**有序**组 $G_1,\dots,G_k$ 的方式，其中每个 $G_i$ 内部构成一个强连通锦标赛图，组间的边全部由顺序强制确定。

**第一步——求 $m$ 点强连通锦标赛图数 $s(m)$。** 任意 $m$ 点锦标赛图都有唯一确定的"第一个"SCC（全序中的源头），大小设为 $t$；剩下 $m-t$ 个点构成一个**完全不受约束**的锦标赛图（因为第一个 SCC 固定后，后面怎样都可以）。按第一个 SCC 的大小 $t$ 对全部 $2^{\binom m2}$ 个 $m$ 点锦标赛图分类：
$$T(m)=\sum_{t=1}^{m}\binom{m}{t}\,s(t)\,T(m-t),\qquad T(m)=2^{\binom m2}\ (m \text{ 点锦标赛图总数})，$$
把 $t=m$ 这一项单独拿出来（此时 $T(0)=1$，这项恰好就是 $s(m)$ 本身）：
$$s(m)=T(m)-\sum_{t=1}^{m-1}\binom{m}{t}\,s(t)\,T(m-t)。$$
对 $m=1,\dots,n$ 用 $O(n^2)$ 的 DP 计算。

**第二步——用指数生成函数（EGF）拼出 $k$ 组。** 设 $G(x)=\sum_{m\ge1}\dfrac{s(m)}{m!}x^m$。把 $n$ 个**带标号**点划分成有序的 $k$ 个非空组、每组内部按 $s(\cdot)$ 计数的方式数，是标准的 EGF 复合规则：
$$f(n,k)=n!\cdot[x^n]\,G(x)^k。$$
实现中维护 `cur` = $G(x)^j$ 的系数（从 $j=1$ 开始不断乘 $G$），每一步读出 $f(n,j)=n!\cdot\text{cur}[n]$。

*验证（$n=3$）：* $s(1)=1,\ s(2)=0,\ s(3)=2$（3 点的 $8$ 个锦标赛图中，只有 3-循环的两种方向是强连通的），故 $G=x+\tfrac13x^3+\dots$。于是 $f(3,1)=6\cdot\tfrac13=2$，$f(3,2)=6\cdot[x^3](x+\tfrac13x^3)^2=6\cdot0=0$（平方的 $x^3$ 项凑不出两个因子的合法组合），$f(3,3)=6\cdot[x^3]x^3=6$——得到 $2,0,6$，与样例输出完全一致。

## Complexity / 复杂度

Computing $s(1..n)$ is $O(n^2)$. Building $G^1,G^2,\dots,G^n$ one multiplication at a time, each a degree-$n$ polynomial convolution truncated to degree $n$, is $O(n^2)$ per step and $O(n)$ steps, i.e. $O(n^3)$ overall. With $n\le500$ this is about $1.25\times10^8$ modular operations, within the time limit.

计算 $s(1..n)$ 需 $O(n^2)$。逐步构造 $G^1,G^2,\dots,G^n$，每次是截断到 $n$ 次的多项式卷积，单步 $O(n^2)$，共 $O(n)$ 步，总体 $O(n^3)$。$n\le500$ 时约 $1.25\times10^8$ 次取模运算，时限内可以完成。
