# 022 - Digit Queries

## Problem / 题目

Consider the infinite string $123456789101112\dots$ obtained by writing all positive integers one after another. For each query $k$, output the $k$-th digit of this string.

考虑把所有正整数依次写出得到的无限字符串 $123456789101112\dots$。对每个查询 $k$，输出该字符串的第 $k$ 个数字。

## Idea / 思路

Group numbers by length: there are $9 \cdot 10^{d-1}$ numbers with exactly $d$ digits, contributing $d \cdot 9 \cdot 10^{d-1}$ digits in total. Starting from $d = 1$, subtract these whole blocks from $k$ until $k$ falls inside the block of $d$-digit numbers. Within that block the target number is $\text{start} + (k-1)/d$ where $\text{start} = 10^{d-1}$, and the answer is the digit at index $(k-1) \bmod d$ of that number.

按长度给数字分组：恰好 $d$ 位的数有 $9 \cdot 10^{d-1}$ 个，共贡献 $d \cdot 9 \cdot 10^{d-1}$ 个数字。从 $d = 1$ 开始，把这些整块从 $k$ 中减去，直到 $k$ 落进 $d$ 位数的块内。在该块中，目标数是 $\text{start} + (k-1)/d$，其中 $\text{start} = 10^{d-1}$，答案就是该数第 $(k-1) \bmod d$ 位的数字。

## Complexity / 复杂度

The number of length blocks is $O(\log k)$, so each query is answered in $O(\log k)$ time.

长度块的数量是 $O(\log k)$，因此每个查询用 $O(\log k)$ 时间回答。
