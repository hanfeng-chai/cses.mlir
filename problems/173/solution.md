# 173 - Christmas Party

## Problem / 题目
Count the permutations of $n$ elements with no fixed point (derangements), modulo $10^9+7$.

求 $n$ 个元素没有不动点的排列（错排）个数，模 $10^9+7$。

## Idea / 思路
Derangements satisfy $D(0)=1$, $D(1)=0$, and $D(n)=(n-1)\big(D(n-1)+D(n-2)\big)$. Iterate the recurrence modulo $p$.

错排满足 $D(0)=1$、$D(1)=0$，以及 $D(n)=(n-1)\big(D(n-1)+D(n-2)\big)$。对该递推取模迭代即可。

## Complexity / 复杂度
$O(n)$. $O(n)$。
