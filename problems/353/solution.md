# 353 - Counting LCM Arrays

## Problem / 题目

Count arrays $a_1,\dots,a_n$ of positive integers with $\operatorname{lcm}(a_i,a_{i+1})=k$ for every $1\le i<n$, modulo $10^9+7$. Several independent $(n,k)$ queries, $n$ up to $10^9$.

求正整数数组 $a_1,\dots,a_n$ 使得每个相邻对都满足 $\operatorname{lcm}(a_i,a_{i+1})=k$ 的数组个数，对 $10^9+7$ 取模。多组独立询问 $(n,k)$，$n$ 可达 $10^9$。

## Idea / 思路

First, $\operatorname{lcm}(a_i,a_{i+1})=k$ forces every $a_i$ to **divide** $k$. Factor $k=\prod_j p_j^{e_j}$. The exponent of $p_j$ in $\operatorname{lcm}(a_i,a_{i+1})$ is $\max(\text{exp}_j(a_i),\text{exp}_j(a_{i+1}))$, and this must equal $e_j$ *independently for every prime* — the constraints completely **decouple across primes**, so the total count is the *product*, over each prime $p_j\mid k$, of the count of valid exponent-sequences for that one prime alone.

For a single prime with exponent $e$: we need sequences $b_1,\dots,b_n\in\{0,\dots,e\}$ with $\max(b_i,b_{i+1})=e$ for every consecutive pair — i.e. **at least one of every consecutive pair must equal $e$ exactly** (neither can exceed $e$, so if neither equals $e$ the max is $<e$). Classify each position as state $E$ (value exactly $e$) or state $O$ (any of the $e$ other values $0,\dots,e-1$); the constraint becomes exactly "no two consecutive $O$'s" — a Fibonacci-like counting problem, weighted by $e$ choices per $O$.

Let $A(n)$ = weighted count of length-$n$ valid state-strings ending in $E$, $B(n)$ ending in $O$. Then $A(n)=A(n-1)+B(n-1)$ (append $E$: always legal) and $B(n)=e\cdot A(n-1)$ (append $O$: only legal after $E$, with $e$ choices for its value); base case $A(1)=1,B(1)=e$. The answer for this prime is $A(n)+B(n)$, computed via $2\times2$ **matrix exponentiation** $\begin{pmatrix}1&1\\e&0\end{pmatrix}^{n-1}$ in $O(\log n)$ — independent of $k$'s actual size, only its (small number of) distinct prime factors matter.

Multiply the per-prime results together (over the at most $\approx9$ distinct primes dividing a $k\le10^9$) to get the final answer; $k=1$ has no prime factors and contributes the empty product $1$ (the only array is all-ones).

*Sanity check:* $k=4=2^2$ ($e=2$): $g(3,2)=11$, matching the sample. $k=6=2\cdot3$ (two primes, each $e=1$): $g(4,1)=8$ for each prime, product $8\times8=64$, matching the sample.

首先，$\operatorname{lcm}(a_i,a_{i+1})=k$ 强制每个 $a_i$ 都**整除** $k$。设 $k=\prod_j p_j^{e_j}$。$\operatorname{lcm}(a_i,a_{i+1})$ 中素数 $p_j$ 的指数是 $\max(\text{exp}_j(a_i),\text{exp}_j(a_{i+1}))$，且必须*对每个素数分别*等于 $e_j$——各个素数上的约束**完全解耦**，所以总数是对 $k$ 的每个素因子 $p_j$ 分别求"只考虑这一个素数时的合法指数序列数"后的**乘积**。

对单个指数为 $e$ 的素数：需要序列 $b_1,\dots,b_n\in\{0,\dots,e\}$，每对相邻满足 $\max(b_i,b_{i+1})=e$——也就是**每对相邻中至少有一个恰好等于 $e$**（两者都不能超过 $e$，所以若都不等于 $e$，最大值就 $<e$）。把每个位置分类为状态 $E$（值恰为 $e$）或状态 $O$（其余 $e$ 个值 $0,\dots,e-1$ 中任意一个），约束就变成"不能有两个连续的 $O$"——一个带权重的斐波那契式计数问题，每个 $O$ 贡献 $e$ 种选择。

设 $A(n)$ = 以 $E$ 结尾的长度 $n$ 合法状态串的加权计数，$B(n)$ = 以 $O$ 结尾的。则 $A(n)=A(n-1)+B(n-1)$（追加 $E$：总是合法），$B(n)=e\cdot A(n-1)$（追加 $O$：只有前一个是 $E$ 才合法，且有 $e$ 种取值）；边界 $A(1)=1,B(1)=e$。该素数对应的答案是 $A(n)+B(n)$，用 $2\times2$ **矩阵快速幂** $\begin{pmatrix}1&1\\e&0\end{pmatrix}^{n-1}$ 在 $O(\log n)$ 内求出——与 $k$ 的具体大小无关，只取决于它（数量很少的）不同素因子。

把各素数（$k\le10^9$ 时不同素因子最多约 $9$ 个）的结果相乘即为答案；$k=1$ 没有素因子，对应空乘积 $1$（唯一的数组是全 $1$）。

*验证：* $k=4=2^2$（$e=2$）：$g(3,2)=11$，与样例一致。$k=6=2\cdot3$（两个素数，$e$ 均为 $1$）：每个素数 $g(4,1)=8$，乘积 $8\times8=64$，与样例一致。

## Complexity / 复杂度

Per query: $O(\sqrt k)$ to factor $k$, plus $O(\log n)$ per distinct prime factor for the $2\times2$ matrix power. With $t\le1000$ queries this is roughly $1000\times(\sqrt{10^9}+9\times30\times8)\approx3\times10^7$.

每次询问：分解 $k$ 需 $O(\sqrt k)$，每个不同素因子的 $2\times2$ 矩阵快速幂需 $O(\log n)$。$t\le1000$ 次询问总计约 $1000\times(\sqrt{10^9}+9\times30\times8)\approx3\times10^7$。
