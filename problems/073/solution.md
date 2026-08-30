# 073 - Money Sums

## Problem / 题目

Given $n$ coins with values, determine every distinct sum that can be formed using a subset of the coins (each coin at most once). Print how many sums and list them increasingly.

给定 $n$ 枚有面值的硬币，求出用硬币子集（每枚至多用一次）能凑出的所有不同金额。输出金额个数并按升序列出.

## Idea / 思路

This is subset-sum reachability. Represent the set of achievable sums as the bits of a bitset, starting with only bit $0$ set (sum $0$ is achievable). For each coin of value $x$, update the bitset with $dp \mathrel{|}= dp \ll x$, which marks every old sum plus $x$ as also achievable. Finally read off the set bits from $1$ to the total.

这是子集和可达性问题。用一个 bitset 的各位表示可达金额集合，初始只置位 $0$（金额 $0$ 可达）。对每枚面值 $x$ 的硬币，用 $dp \mathrel{|}= dp \ll x$ 更新，把每个旧金额加上 $x$ 也标为可达。最后从 $1$ 到总和读出被置位的金额即可。

## Complexity / 复杂度

With total sum $S$, the bitset shifts cost $O(nS/w)$ where $w$ is the machine word size — very fast.

设总和为 $S$，bitset 移位的代价为 $O(nS/w)$，$w$ 为机器字长，非常快。
