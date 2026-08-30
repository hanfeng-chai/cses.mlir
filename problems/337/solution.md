# 337 - Counting Reorders

## Problem / 题目

Given a string, count the distinct reorderings of its characters such that no two adjacent characters are equal, modulo $10^9+7$.

给定一个字符串，求它的字符重新排列中，没有两个相邻字符相同的排列个数，对 $10^9+7$ 取模。

## Idea / 思路

This is the classic "Smirnov word" counting problem (words over a multiset alphabet with no equal adjacent letters). The trick is an inclusion–exclusion over *gluing*: for a letter that appears $c$ times, imagine merging its $c$ copies into $k$ maximal contiguous blocks ($1\le k\le c$); gluing captures (and, with alternating signs, cancels out) the over-counting caused by two copies of the same letter ending up adjacent when we later shuffle all the blocks together freely. For a single letter with count $c$, the signed weight of using exactly $k$ blocks is
$$g(c,k)=(-1)^{c-k}\binom{c-1}{k-1}\frac{1}{k!}.$$
Here $\binom{c-1}{k-1}$ counts the ways to split $c$ identical copies into $k$ ordered nonempty groups (a standard "stars and bars" composition count), and dividing by $k!$ accounts for the fact that the $k$ blocks of *the same letter* end up indistinguishable once we count final arrangements (we multiply by a single global $T!$ at the very end, treating all blocks — from every letter — as if they were on labeled slots, so we must divide out the redundancy from each letter's own blocks here).

Combine all distinct letters by convolution: if letter $L$ contributes the polynomial $P_L(x)=\sum_k g(c_L,k)x^k$ (a generating function tracking "total blocks used"), then the product $\prod_L P_L(x)$ has a coefficient at $x^T$ equal to the signed count of ways to choose block-splits for every letter so that $T$ blocks result in total. Finally, the actual answer sums over $T$, weighting by $T!$ (the number of ways to arrange $T$ distinguishable blocks in a row):
$$\text{answer}=\sum_{T} T!\cdot[x^T]\prod_L P_L(x).$$

*Sanity check (`aabc`, expected $6$):* letter `a` ($c=2$) contributes $g(2,1)=-1,\ g(2,2)=\tfrac12$; letters `b`,`c` ($c=1$) each contribute only $g(1,1)=1$. The product is $(-x+\tfrac12x^2)\cdot x\cdot x=-x^3+\tfrac12x^4$, so answer $=3!\cdot(-1)+4!\cdot\tfrac12=-6+12=6$ — matching exactly.

The implementation keeps a running DP array `dp[T]` (the polynomial product built up letter by letter) and, for the current letter with count `ci`, convolves in $g(ci,k)$ for $k=1..ci$.

这是经典的"Smirnov 词"计数问题（多重集字母表中没有相邻相同字母的排列）。技巧是对"粘合"做容斥：对出现 $c$ 次的某个字母，设想把它的 $c$ 个拷贝合并成 $k$ 个极大连续块（$1\le k\le c$）；粘合捕捉（并用交替符号抵消）了之后把所有块自由打乱重排时，同字母两拷贝恰好相邻所导致的重复计数。对单个出现 $c$ 次的字母，恰好用 $k$ 个块的带符号权重是
$$g(c,k)=(-1)^{c-k}\binom{c-1}{k-1}\frac{1}{k!}。$$
其中 $\binom{c-1}{k-1}$ 是把 $c$ 个相同拷贝拆成 $k$ 个有序非空组的方式数（标准的"隔板法"组合数），除以 $k!$ 是因为最终统计排列数时，同一个字母的这 $k$ 个块彼此不可区分（我们最后统一乘以一个全局的 $T!$，把所有字母的所有块当作占据了带编号的位置，因此这里要先把每个字母自己 $k$ 个块的冗余除掉）。

把所有不同字母按卷积合并：若字母 $L$ 贡献多项式 $P_L(x)=\sum_k g(c_L,k)x^k$（记录"总共用了多少块"的生成函数），则乘积 $\prod_L P_L(x)$ 在 $x^T$ 处的系数，就是"每个字母都选好拆块方式、总共恰好 $T$ 块"的带符号方案数之和。最后答案对 $T$ 求和，每项乘以 $T!$（把 $T$ 个可区分的块排成一行的方式数）：
$$\text{答案}=\sum_{T} T!\cdot[x^T]\prod_L P_L(x)。$$

*验证（`aabc`，期望答案 $6$）：* 字母 `a`（$c=2$）贡献 $g(2,1)=-1,\ g(2,2)=\tfrac12$；字母 `b`、`c`（$c=1$）各只贡献 $g(1,1)=1$。乘积为 $(-x+\tfrac12x^2)\cdot x\cdot x=-x^3+\tfrac12x^4$，故答案 $=3!\cdot(-1)+4!\cdot\tfrac12=-6+12=6$，与期望完全一致。

实现中维护一个滚动 DP 数组 `dp[T]`（逐字母累乘构造出的多项式），对当前字母（出现次数 `ci`）依次卷入 $g(ci,k)$，$k=1..ci$。

## Complexity / 复杂度

For each distinct letter with count $c_i$, the convolution step costs $O(c_i\cdot n)$ in the worst case (current polynomial degree up to $n$), so the total is $O(n^2)$ in the worst case (e.g. two letters each with $\approx n/2$ copies). With $n\le5000$ this is about $2.5\times10^7$ operations.

对每个出现次数为 $c_i$ 的不同字母，卷积一步最坏代价 $O(c_i\cdot n)$（当前多项式次数至多为 $n$），故最坏总体 $O(n^2)$（例如只有两个字母各占 $\approx n/2$ 次）。$n\le5000$ 时约 $2.5\times10^7$ 次操作。
