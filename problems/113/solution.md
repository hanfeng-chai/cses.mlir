# 113 - Hamiltonian Flights

## Problem / 题目

Count the routes from city $1$ to city $n$ that visit every city exactly once, modulo $10^9+7$ (with $n \le 20$).

统计从城市 $1$ 到城市 $n$、恰好经过每座城市一次的路线数，对 $10^9+7$ 取模（$n \le 20$）。

## Idea / 思路

This is counting Hamiltonian paths, done with **bitmask dynamic programming**. Let $dp[\text{mask}][v]$ be the number of routes that start at city $1$, visit exactly the set $\text{mask}$, and currently sit at city $v$. The base is $dp[\{1\}][1]=1$, and for each mask we extend by an incoming edge $u\to v$: $dp[\text{mask}][v] = \sum_{u} dp[\text{mask}\setminus\{v\}][u]$ over predecessors $u$ in the mask. The answer is $dp[\text{full}][n]$.

这是哈密顿路径计数，用**状压动态规划**完成。设 $dp[\text{mask}][v]$ 为从城市 $1$ 出发、恰好访问集合 $\text{mask}$、当前位于城市 $v$ 的路线数。初值 $dp[\{1\}][1]=1$，对每个 mask 用入边 $u\to v$ 扩展：$dp[\text{mask}][v] = \sum_{u} dp[\text{mask}\setminus\{v\}][u]$，$u$ 取 mask 内的前驱。答案为 $dp[\text{full}][n]$。

## Complexity / 复杂度

There are $2^n \cdot n$ states each summing over predecessors, so the time is $O(2^n \cdot n^2)$ in the worst case.

共 $2^n \cdot n$ 个状态、每个对前驱求和，因此最坏时间为 $O(2^n \cdot n^2)$。
