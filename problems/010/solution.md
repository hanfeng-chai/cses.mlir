# 010 - Trailing Zeros

## Problem / 题目

We must count the number of trailing zeros in $n!$ (the factorial of $n$).

我们要统计 $n!$（$n$ 的阶乘）末尾零的个数。

## Idea / 思路

A trailing zero is produced by a factor of $10 = 2 \times 5$. In a factorial there are always more factors of $2$ than of $5$, so the number of trailing zeros equals the number of times $5$ divides $n!$. By Legendre's formula, that count is $\lfloor n/5 \rfloor + \lfloor n/25 \rfloor + \lfloor n/125 \rfloor + \cdots$ — we add how many multiples of $5$, of $25$, of $125$, and so on, are at most $n$.

末尾的零是由因子 $10 = 2 \times 5$ 产生的。在阶乘中因子 $2$ 总是比因子 $5$ 多，所以末尾零的个数等于 $5$ 整除 $n!$ 的次数。根据勒让德公式（Legendre's formula），这个次数是 $\lfloor n/5 \rfloor + \lfloor n/25 \rfloor + \lfloor n/125 \rfloor + \cdots$ ——也就是把不超过 $n$ 的 $5$ 的倍数、$25$ 的倍数、$125$ 的倍数……的个数累加起来。

## Complexity / 复杂度

The loop multiplies the divisor by $5$ each step, so it runs in $O(\log_5 n)$ time — only a handful of iterations even for $n = 10^9$.

循环每一步把除数乘以 $5$，所以运行时间为 $O(\log_5 n)$ ——即使 $n = 10^9$ 也只需要很少的几次迭代。
