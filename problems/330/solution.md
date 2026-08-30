# 330 - Empty String

## Problem / 题目

You are given a string of length $n$. On each move you may delete two *adjacent, equal* characters. Count, modulo $10^9+7$, the number of distinct move sequences that remove the entire string.

给定一个长度为 $n$ 的字符串。每次操作可以删除两个**相邻且相等**的字符。求把整个字符串删空的不同操作序列数，对 $10^9+7$ 取模。

## Idea / 思路

If the whole string can be erased, the very first character $s[i]$ must eventually be removed *together with* some later occurrence of the same letter $s[k]$ ($s[k]=s[i]$) — and at that moment they must be adjacent, which means **everything strictly between them, $s[i+1..k-1]$, must already have been completely erased**. This gives the recursive structure of an interval DP:

$$dp[i][j]=\text{number of move-sequences that empty } s[i..j]\quad(\text{only defined when } j-i+1 \text{ is even}).$$

For each candidate partner $k$ of $s[i]$ with $s[k]=s[i]$ (so that the "inside" range $[i+1,k-1]$ has even length), the pair $(i,k)$ splits the range into three independent zones: the **inside** $[i+1,k-1]$ (must be fully cleared *before* $i,k$ can be removed), the pair $(i,k)$ itself (one move), and the **outside** $[k+1,j]$ (its moves have no interaction with $i,k$ at all, since those cells are strictly to the right of $k$).

The subtlety is that the answer counts *distinct orderings of moves*, not just matchings — so we must count how many ways to **interleave** the $q=\frac{k-i-1}{2}$ inside moves (followed immediately by the $(i,k)$ removal, so this whole "inside + final pair" chunk of $q+1$ moves keeps its own relative order fixed) with the $r=\frac{j-k}{2}$ outside moves (which can happen in any relative position, since they're independent). Interleaving two order-preserving sequences of lengths $q+1$ and $r$ into one combined sequence of length $p=q+1+r$ can be done in $\binom{p}{r}$ ways (choose which $r$ of the $p$ slots belong to the outside stream). Multiplying in the internal orderings $dp[i+1][k-1]$ (inside) and $dp[k+1][j]$ (outside):

$$dp[i][j]=\sum_{\substack{k>i,\ (k-i) \text{ odd}\\ s[k]=s[i]}} dp[i+1][k-1]\cdot dp[k+1][j]\cdot\binom{p}{r},\qquad p=\tfrac{j-i+1}{2},\ r=\tfrac{j-k}{2}.$$

Base case: an empty range has exactly $1$ (trivial) way to be emptied, so `get(i,j)` returns $1$ when $i>j$. Binomial coefficients up to $n/2$ are precomputed with Pascal's triangle. The answer is $dp[0][n-1]$.

如果整个字符串能被删空，那么最左边的字符 $s[i]$ 最终一定会和后面某个同字母的位置 $s[k]$（$s[k]=s[i]$）一起被删掉——而删除那一刻它俩必须相邻，也就是说**它们之间的所有字符 $s[i+1..k-1]$ 此时必须已经被完全删空**。这就给出了区间 DP 的递归结构：

$$dp[i][j]=\text{把 } s[i..j] \text{ 删空的操作序列数}\quad(\text{仅当 } j-i+1 \text{ 为偶数时有定义})。$$

对 $s[i]$ 的每个候选搭档 $k$（$s[k]=s[i]$，使"内部"区间 $[i+1,k-1]$ 长度为偶数），配对 $(i,k)$ 把区间分成三个互不干扰的部分：**内部** $[i+1,k-1]$（必须先被清空，$i,k$ 才能相邻）、配对 $(i,k)$ 本身（一次操作）、**外部** $[k+1,j]$（这些操作完全不受 $i,k$ 影响，因为它们严格在 $k$ 右边）。

微妙之处在于答案数的是**不同的操作顺序**，不只是配对方式——所以要数清楚：把"内部的 $q=\frac{k-i-1}{2}$ 次操作，紧跟着 $(i,k)$ 这一次删除"（这一整块 $q+1$ 次操作，相对顺序被固定，作为一条"流"）与"外部的 $r=\frac{j-k}{2}$ 次操作"（相对顺序独立，作为另一条"流"）**交错**在一起有多少种方式。把两条各自保持内部顺序、长度分别为 $q+1$ 和 $r$ 的"流"合并成长度 $p=q+1+r$ 的序列，方法数是 $\binom{p}{r}$（在 $p$ 个位置里选出 $r$ 个给外部流）。再乘上内部的排序方式数 $dp[i+1][k-1]$（内部）与 $dp[k+1][j]$（外部）：

$$dp[i][j]=\sum_{\substack{k>i,\ (k-i)\text{ 为奇数}\\ s[k]=s[i]}} dp[i+1][k-1]\cdot dp[k+1][j]\cdot\binom{p}{r},\qquad p=\tfrac{j-i+1}{2},\ r=\tfrac{j-k}{2}。$$

边界：空区间恰好有 $1$ 种（什么都不用做的）删空方式，所以 `get(i,j)` 在 $i>j$ 时返回 $1$。组合数预处理到 $n/2$（帕斯卡三角）。答案为 $dp[0][n-1]$。

## Complexity / 复杂度

There are $O(n)$ choices of even length, $O(n)$ starting positions $i$, and $O(n)$ candidate partners $k$, giving $O(n^3)$ time — with $n\le500$ this is about $1.25\times10^8$ simple modular operations, comfortably within the time limit. Memory is $O(n^2)$ for the DP table.

区间长度 $O(n)$ 种取值、起点 $i$ 共 $O(n)$ 种、搭档 $k$ 共 $O(n)$ 种候选，总时间 $O(n^3)$——$n\le500$ 时约 $1.25\times10^8$ 次简单取模运算，时限内可以轻松跑完。DP 表占用 $O(n^2)$ 内存。
