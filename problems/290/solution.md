# 290 - Permutation Prime Sums

## Problem / 题目
Construct two permutations $a,b$ of $1..n$ such that every $a_i+b_i$ is prime.

构造 $1..n$ 的两个排列 $a,b$ 使每个 $a_i+b_i$ 都是素数。

## Idea / 思路
Take $a$ as the identity. Process the values $1..n$ from the top down: by Bertrand's postulate there is a prime $p$ in $(\text{hi},2\,\text{hi}]$; pair every position $i\in[p-\text{hi},\text{hi}]$ with $b_i=p-i$ so that $i+b_i=p$ is prime, which covers the block of values $[p-\text{hi},\text{hi}]$. Recurse on the remaining lower block. A solution always exists.

取 $a$ 为恒等。把值 $1..n$ 从高到低处理：由 Bertrand 公设，$(\text{hi},2\,\text{hi}]$ 内有素数 $p$；对每个位置 $i\in[p-\text{hi},\text{hi}]$ 令 $b_i=p-i$，使 $i+b_i=p$ 为素数，覆盖值块 $[p-\text{hi},\text{hi}]$。对剩余较低块递归。解总存在。

## Multi-solution / 多解
Any valid pair is accepted; a custom checker verifies both are permutations and all sums are prime.

任意合法对均可；checker 验证两者都是排列且所有和为素数。

## Complexity / 复杂度
$O(n\log\log n)$. $O(n\log\log n)$。
