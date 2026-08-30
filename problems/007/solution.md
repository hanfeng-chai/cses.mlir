# 007 - Two Knights

## Problem / 题目

For each $k = 1, 2, \ldots, n$ we must count the number of ways to place two knights on a $k \times k$ chessboard so that they do not attack each other.

对每个 $k = 1, 2, \ldots, n$，我们要统计在 $k \times k$ 棋盘上放置两个骑士、且它们互不攻击的方案数。

## Idea / 思路

Count all placements and subtract the bad ones. The number of ways to choose two distinct squares out of $k^2$ is $\binom{k^2}{2} = \frac{k^2(k^2-1)}{2}$. Two knights attack each other exactly when they sit at opposite corners of a $2 \times 3$ or $3 \times 2$ rectangle. There are $(k-1)(k-2)$ rectangles of each orientation, and each rectangle gives $2$ attacking pairs, so the number of attacking placements is $4(k-1)(k-2)$.

先数出所有放法，再减去不合法的。从 $k^2$ 个格子中选两个不同格子的方案数是 $\binom{k^2}{2} = \frac{k^2(k^2-1)}{2}$。两个骑士互相攻击，当且仅当它们位于某个 $2 \times 3$ 或 $3 \times 2$ 矩形的对角。每种朝向各有 $(k-1)(k-2)$ 个这样的矩形，每个矩形贡献 $2$ 对攻击位置，所以互相攻击的放法共有 $4(k-1)(k-2)$ 个。

So the answer for each $k$ is $\frac{k^2(k^2-1)}{2} - 4(k-1)(k-2)$.

因此每个 $k$ 的答案是 $\frac{k^2(k^2-1)}{2} - 4(k-1)(k-2)$。

## Watch out / 注意

For $k$ up to $10^4$, $k^2$ reaches $10^8$ and $\frac{k^2(k^2-1)}{2}$ reaches about $5 \times 10^{15}$, so we use `long long`.

当 $k$ 达到 $10^4$ 时，$k^2$ 达到 $10^8$，$\frac{k^2(k^2-1)}{2}$ 达到约 $5 \times 10^{15}$，所以使用 `long long`。

## Complexity / 复杂度

$O(1)$ per value of $k$, $O(n)$ in total.

每个 $k$ 的计算是 $O(1)$，总体 $O(n)$。
