# 340 - Functional Graph Distribution

## Problem / 题目

A *functional graph* on $n$ labeled nodes is a directed graph where every node has out-degree exactly $1$ (i.e. it encodes a function $f:\{1,\dots,n\}\to\{1,\dots,n\}$). For each $k=1,\dots,n$, count the functional graphs on $n$ nodes with exactly $k$ (weakly) connected components, modulo $10^9+7$.

$n$ 个带标号点上的"函数图"是每个点出度恰好为 $1$ 的有向图（即编码了一个函数 $f:\{1,\dots,n\}\to\{1,\dots,n\}$）。对每个 $k=1,\dots,n$，求恰好有 $k$ 个（弱）连通分量的 $n$ 点函数图个数，对 $10^9+7$ 取模。

## Idea / 思路

**Structural fact.** Every connected component of a functional graph looks like a single cycle with rooted trees hanging off the cycle nodes, with all tree edges pointing *toward* the cycle (a "rho" shape: $\rho$). So the number of components equals the number of **cycles** once you know exactly which nodes lie on some cycle.

**Step 1 — choose which $s$ nodes are "on a cycle" and attach the rest as trees.** By a classical generalization of Cayley's formula, the number of labeled forests on $n$ nodes made of trees rooted at a *specified* set of $s$ nodes (edges pointing toward the roots) is
$$\text{forest}(n,s)=\begin{cases}1,& s=n\ (\text{every node is its own root, no edges}),\\ s\cdot n^{\,n-s-1},& 1\le s<n.\end{cases}$$
So the number of ways to pick *which* $s$ of the $n$ labeled nodes end up on some cycle, and attach the other $n-s$ nodes as a forest of trees feeding into them, is
$$w(s)=\binom{n}{s}\cdot\text{forest}(n,s).$$

**Step 2 — arrange the $s$ cycle-nodes into cycles.** Once we know which $s$ nodes are on cycles, the restriction of $f$ to those $s$ nodes must be a **permutation of that set** (each maps to another cycle-node, bijectively) — and a permutation's cycle decomposition is exactly a set of graph-cycles! The number of connected components of the whole functional graph equals the number of cycles of this permutation. The number of permutations of $s$ elements with exactly $k$ cycles is the unsigned Stirling number of the first kind $\left[s\atop k\right]$. So
$$f(n,k)=\sum_{s=1}^{n}\binom{n}{s}\,\text{forest}(n,s)\,\left[s\atop k\right]=\sum_{s=1}^n w(s)\left[s\atop k\right].$$

**Step 3 — avoid an explicit Stirling table using the rising-factorial identity.** Unsigned Stirling numbers of the first kind are exactly the coefficients of the rising factorial: $y^{(s)}:=y(y+1)(y+2)\cdots(y+s-1)=\sum_{k}\left[s\atop k\right]y^k$. So
$$f(n,k)=[y^k]\sum_{s=1}^n w(s)\cdot y(y+1)\cdots(y+s-1).$$
The implementation builds the polynomial $p_s(y)=y(y+1)\cdots(y+s-1)$ incrementally: going from $s-1$ to $s$ just multiplies in one more factor $(y+(s-1))$, i.e. `p[d] = p[d-1] + (s-1)*p[d]` from high degree to low (in-place multiply by a linear factor). After updating $p$ for the current $s$, it accumulates $R\mathrel{+}= w(s)\cdot p$ coefficient-wise. At the end, $R[k]=f(n,k)$ directly — no extra normalization is needed because $w(s)$ already counts *labeled* structures.

*Sanity check ($n=3$):* $\text{forest}(3,1)=1\cdot3^1=3,\ \text{forest}(3,2)=2\cdot3^0=2,\ \text{forest}(3,3)=1$, so $w(1)=3\cdot3=9,\ w(2)=3\cdot2=6,\ w(3)=1\cdot1=1$. The rising factorials are $p_1=y,\ p_2=y^2+y,\ p_3=y^3+3y^2+2y$. Then $R=9y+6(y^2+y)+(y^3+3y^2+2y)=y^3+9y^2+17y$, giving $(f(3,1),f(3,2),f(3,3))=(17,9,1)$ — exactly the sample output.

**结构事实。** 函数图的每个连通分量都是一个环，环上的每个点挂着一棵指向环的有根树（"$\rho$ 形"结构）。所以一旦确定了哪些点在某个环上，连通分量数就等于**环的个数**。

**第一步——选定哪 $s$ 个点"在环上"，其余的挂成树。** 由 Cayley 公式的一个经典推广，$n$ 个点上、树根为**指定的** $s$ 个点（边指向根）的带标号森林个数是
$$\text{forest}(n,s)=\begin{cases}1,& s=n\ (\text{每个点自成一棵树，没有边}),\\ s\cdot n^{\,n-s-1},& 1\le s<n。\end{cases}$$
所以选定 $n$ 个带标号点中哪 $s$ 个最终落在某个环上、并把剩下 $n-s$ 个点接成指向它们的森林的方式数是
$$w(s)=\binom{n}{s}\cdot\text{forest}(n,s)。$$

**第二步——把这 $s$ 个"环上点"排成环。** 一旦知道哪 $s$ 个点在环上，$f$ 限制在这 $s$ 个点上必然是这个集合的一个**置换**（每个点映到另一个环上点，构成双射）——而置换的循环分解本身就是一组图上的环！整个函数图的连通分量数，就等于这个置换的循环个数。$s$ 元置换恰好有 $k$ 个循环的个数，正是无符号第一类斯特林数 $\left[s\atop k\right]$。所以
$$f(n,k)=\sum_{s=1}^{n}\binom{n}{s}\,\text{forest}(n,s)\,\left[s\atop k\right]=\sum_{s=1}^n w(s)\left[s\atop k\right]。$$

**第三步——用升阶乘恒等式避免显式斯特林数表。** 无符号第一类斯特林数恰好是升阶乘的系数：$y^{(s)}:=y(y+1)(y+2)\cdots(y+s-1)=\sum_{k}\left[s\atop k\right]y^k$。所以
$$f(n,k)=[y^k]\sum_{s=1}^n w(s)\cdot y(y+1)\cdots(y+s-1)。$$
实现增量构造多项式 $p_s(y)=y(y+1)\cdots(y+s-1)$：从 $s-1$ 到 $s$ 只需再乘入一个因子 $(y+(s-1))$，即从高次到低次原地更新 `p[d] = p[d-1] + (s-1)*p[d]`（原地乘一个一次多项式）。每次更新完当前 $s$ 的 $p$ 后，把 $R\mathrel{+}= w(s)\cdot p$ 逐项累加。最终 $R[k]=f(n,k)$，无需额外归一化，因为 $w(s)$ 本身已经是"带标号"结构的计数。

*验证（$n=3$）：* $\text{forest}(3,1)=1\cdot3^1=3,\ \text{forest}(3,2)=2\cdot3^0=2,\ \text{forest}(3,3)=1$，故 $w(1)=3\cdot3=9,\ w(2)=3\cdot2=6,\ w(3)=1\cdot1=1$。升阶乘为 $p_1=y,\ p_2=y^2+y,\ p_3=y^3+3y^2+2y$。于是 $R=9y+6(y^2+y)+(y^3+3y^2+2y)=y^3+9y^2+17y$，得 $(f(3,1),f(3,2),f(3,3))=(17,9,1)$，与样例输出完全一致。

## Complexity / 复杂度

Computing all $\text{forest}(n,s)$ and $w(s)$ is $O(n\log n)$ (fast exponentiation per $s$). Incrementally building $p_s$ and accumulating $R$ for $s=1,\dots,n$ costs $O(n)$ per step (updating a degree-$\le n$ polynomial), so $O(n^2)$ overall. With $n\le5000$ this is about $2.5\times10^7$ operations.

计算所有 $\text{forest}(n,s)$ 与 $w(s)$ 需 $O(n\log n)$（每个 $s$ 一次快速幂）。为 $s=1,\dots,n$ 增量构造 $p_s$ 并累加 $R$，每步 $O(n)$（更新一个次数 $\le n$ 的多项式），总体 $O(n^2)$。$n\le5000$ 时约 $2.5\times10^7$ 次操作。
