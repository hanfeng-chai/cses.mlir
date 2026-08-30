# 101 - Planets Queries I

## Problem / 题目

Each of $n$ planets has one teleporter to another planet. For each query $(x, k)$, report the planet reached by starting at $x$ and following $k$ teleporters ($k$ up to $10^9$).

$n$ 颗行星每颗有一个通往另一行星的传送门。对每个询问 $(x, k)$，报告从 $x$ 出发跟随 $k$ 次传送后到达的行星（$k$ 至多 $10^9$）。

## Idea / 思路

This is the "$k$-th successor in a functional graph" problem, solved with **binary lifting**. Precompute $up[j][v]$ = the planet reached from $v$ after $2^j$ teleporters, using $up[j][v] = up[j-1][up[j-1][v]]$. To answer $(x,k)$, jump along the set bits of $k$: for each bit $j$ set in $k$, replace $x$ with $up[j][x]$.

这是"函数图中第 $k$ 个后继"问题，用**二进制提升**解决。预处理 $up[j][v]$ = 从 $v$ 经 $2^j$ 次传送到达的行星，递推 $up[j][v] = up[j-1][up[j-1][v]]$。回答 $(x,k)$ 时按 $k$ 的二进制位跳：对 $k$ 中每个置位 $j$，把 $x$ 替换为 $up[j][x]$。

## Complexity / 复杂度

Preprocessing is $O(n\log K)$ and each query is $O(\log K)$ where $K$ is the max jump.

预处理 $O(n\log K)$，每个询问 $O(\log K)$，$K$ 为最大跳数。
