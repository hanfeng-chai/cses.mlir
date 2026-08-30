# 171 - Creating Strings II

## Problem / 题目
Count the distinct permutations (anagrams) of a given string, modulo $10^9+7$.

求给定字符串的不同排列（字母异位词）个数，模 $10^9+7$。

## Idea / 思路
With letter counts $c_a$ and total length $L=\sum c_a$, the answer is the multinomial coefficient $\dfrac{L!}{\prod_a c_a!}$. Compute factorials and divide using modular inverses.

设各字母计数为 $c_a$、总长 $L=\sum c_a$，答案即多项式系数 $\dfrac{L!}{\prod_a c_a!}$。用阶乘配合模逆元做除法。

## Complexity / 复杂度
$O(L+\Sigma\log p)$ with alphabet $\Sigma=26$. $O(L+\Sigma\log p)$，字母表 $\Sigma=26$。
