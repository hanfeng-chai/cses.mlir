# 162 - Exponentiation II

## Problem / 题目
Compute $a^{b^c} \bmod (10^9+7)$ for each query.

对每个询问计算 $a^{b^c} \bmod (10^9+7)$。

## Idea / 思路
Since $p=10^9+7$ is prime and $0<a<p$, Fermat's little theorem gives $a^{x}\equiv a^{x \bmod (p-1)}\pmod p$. So reduce the huge exponent to $e=b^c\bmod(p-1)$ with one fast exponentiation, then compute $a^e\bmod p$. Handle $a=0$ separately: the result is $1$ only when the true exponent $b^c=0$ (i.e. $b=0,c>0$), otherwise $0$.

由于 $p=10^9+7$ 是质数且 $0<a<p$，由费马小定理 $a^{x}\equiv a^{x \bmod (p-1)}\pmod p$。于是先用快速幂把巨大的指数降为 $e=b^c\bmod(p-1)$，再算 $a^e\bmod p$。$a=0$ 需单独处理：仅当真实指数 $b^c=0$（即 $b=0,c>0$）时结果为 $1$，否则为 $0$。

## Complexity / 复杂度
$O(\log c+\log p)$ per query. 每个询问 $O(\log c+\log p)$。
