# 360 - Subsets with Fixed Average

## Problem / 题目

Count the non-empty subsets of an array whose average equals a given value $a$, modulo $10^9+7$.

求数组中平均值恰为给定值 $a$ 的非空子集个数，对 $10^9+7$ 取模。

## Idea / 思路

A subset has average $a$ iff its sum equals $a$ times its size — equivalently, iff $\sum_{i\in\text{subset}}(x_i-a)=0$. Substituting $y_i=x_i-a$ (which can now be *negative*, since $x_i$ or $a$ can each be up to $500$), the problem becomes the standard **subset-sum counting DP**: $dp[\text{sum}]$ = number of subsets with that exact sum of $y$-values, built one element at a time.

Since sums can be negative, offset the DP array by a constant (large enough to cover the worst case $\pm500\times500$) so all indices stay non-negative. For each element with value $y$: if $y\ge0$, update the DP array from **high index to low** ($dp[s]\mathrel{+}=dp[s-y]$, scanning $s$ downward) so that each element is only counted once (standard 0/1-knapsack trick); if $y<0$, the roles of "old" and "new" flip, so scan **low to high** instead, for the same reason (in both cases we must read the *not-yet-updated-this-round* value of $dp[s-y]$).

The answer is $dp[0]-1$ (subtract the empty subset, whose sum is trivially $0$).

某个子集的平均值等于 $a$，当且仅当它的和等于 $a$ 乘以它的大小——等价于 $\sum_{i\in\text{子集}}(x_i-a)=0$。令 $y_i=x_i-a$（现在可能为*负数*，因为 $x_i$、$a$ 各自都可达 $500$），问题就变成标准的**子集和计数 DP**：$dp[\text{和}]$ = 恰好这个 $y$ 值总和的子集个数，逐个元素构造。

由于和可能为负，把 DP 数组的下标整体偏移一个足够大的常数（要覆盖最坏情况 $\pm500\times500$），保证下标始终非负。对每个取值为 $y$ 的元素：若 $y\ge0$，从**高位到低位**更新数组（$dp[s]\mathrel{+}=dp[s-y]$，$s$ 从大到小扫描），这样每个元素只会被计入一次（标准 0/1 背包技巧）；若 $y<0$，"旧值"和"新值"的角色互换，所以改为从**低位到高位**扫描，原因相同（两种情形都必须读到"本轮尚未被更新过"的 $dp[s-y]$）。

答案是 $dp[0]-1$（减去空子集，它的和显然是 $0$）。

## Complexity / 复杂度

$O(n\cdot R)$ time and $O(R)$ memory, where $R\approx2\times n\times500$ is the offset DP array's range. With $n\le500$ this is about $500\times500001\approx2.5\times10^8$ simple array operations.

时间 $O(n\cdot R)$，空间 $O(R)$，其中 $R\approx2\times n\times500$ 是偏移后 DP 数组的范围。$n\le500$ 时约 $500\times500001\approx2.5\times10^8$ 次简单数组操作。
