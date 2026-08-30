# 176 - Bracket Sequences I

## Problem / 题目
Count the valid (balanced) bracket sequences of length $n$, modulo $10^9+7$.

求长度为 $n$ 的合法（匹配）括号序列个数，模 $10^9+7$。

## Idea / 思路
If $n$ is odd the answer is $0$. Otherwise with $h=n/2$ the count is the Catalan number $C_h=\binom{n}{h}-\binom{n}{h+1}$. Precompute factorials for the binomials.

若 $n$ 为奇数答案为 $0$。否则令 $h=n/2$，个数为卡特兰数 $C_h=\binom{n}{h}-\binom{n}{h+1}$。预处理阶乘以求二项式。

## Complexity / 复杂度
$O(n)$ preprocessing, $O(1)$ query. 预处理 $O(n)$，询问 $O(1)$。
