# 149 - Company Queries I

## Problem / 题目

In a company hierarchy (a rooted tree), answer queries: who is employee $x$'s boss $k$ levels up, or $-1$ if none exists?

在公司层级（有根树）中回答询问：员工 $x$ 上数 $k$ 级的老板是谁，若不存在则 $-1$？

## Idea / 思路

Use **binary lifting**. Precompute $up[j][x]$ = the ancestor $2^j$ levels above $x$, with $up[j][x] = up[j-1][up[j-1][x]]$ and a sentinel $0$ for "no boss". To climb $k$ levels, jump along the set bits of $k$; if we ever reach the sentinel $0$ the answer is $-1$.

使用**二进制提升**。预处理 $up[j][x]$ = $x$ 上方 $2^j$ 级的祖先，$up[j][x] = up[j-1][up[j-1][x]]$，并用哨兵 $0$ 表示"无老板"。要上爬 $k$ 级，沿 $k$ 的二进制位跳；若途中到达哨兵 $0$ 则答案为 $-1$。

## Complexity / 复杂度

Preprocessing is $O(n\log n)$ and each query is $O(\log n)$.

预处理 $O(n\log n)$，每个询问 $O(\log n)$。
