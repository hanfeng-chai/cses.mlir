# 335 - Counting Permutations

## Problem / 题目

A permutation of $1,\dots,n$ is *beautiful* if no two **adjacent** elements differ by exactly $1$. Count the beautiful permutations of $1,\dots,n$, modulo $10^9+7$.

若排列 $1,\dots,n$ 中没有任何两个**相邻**元素相差恰好 $1$，就称它是"美丽的"。求 $1,\dots,n$ 的美丽排列数，对 $10^9+7$ 取模。

## Idea / 思路

This is a well-known combinatorial sequence (sometimes called *Hertzsprung's problem*, OEIS A002464): the number of permutations of $n$ where no value is adjacent to a value exactly $1$ away. It can in principle be derived by inclusion–exclusion over which of the $n-1$ "bad adjacent pairs" $\{v,v+1\}$ are forced to sit next to each other (a "cluster method" / permanent-of-a-banded-matrix computation), but the resulting closed form simplifies to a short linear recurrence, which is what the implementation uses directly:

$$a(0)=1,\ a(1)=1,\ a(2)=0,\ a(3)=0,$$
$$a(n)=(n+1)a(n-1)-(n-2)a(n-2)-(n-5)a(n-3)+(n-3)a(n-4)\quad(n\ge4).$$

*Sanity check:* $a(4)=5\cdot0-2\cdot0-(-1)\cdot1+1\cdot1=2$, and $a(5)=6\cdot2-3\cdot0-0\cdot0+2\cdot1=14$, matching the example ($n=5\Rightarrow14$). The sequence continues $1,1,0,0,2,14,90,646,\dots$

Since the recurrence is linear with coefficients that are simple functions of $n$ (not a fixed-order linear recurrence with *constant* coefficients — the coefficients grow with $n$), it must be evaluated by direct forward computation from the base cases up to $n$, rather than sped up with matrix exponentiation; this is still only $O(n)$ time, which is fast enough since $n\le1000$.

这是一个著名的组合数列（有时称为 *Hertzsprung 问题*，OEIS A002464）：$n$ 元排列中，任何值都不与恰好相差 $1$ 的值相邻的排列数。原则上可以用容斥原理，枚举 $n-1$ 个"坏相邻对" $\{v,v+1\}$ 中哪些被强制相邻（即"簇方法"/带状矩阵积和式计算）来推导，但最终结果化简为一个简短的线性递推式，实现直接使用它：

$$a(0)=1,\ a(1)=1,\ a(2)=0,\ a(3)=0,$$
$$a(n)=(n+1)a(n-1)-(n-2)a(n-2)-(n-5)a(n-3)+(n-3)a(n-4)\quad(n\ge4)。$$

*验证：* $a(4)=5\cdot0-2\cdot0-(-1)\cdot1+1\cdot1=2$，$a(5)=6\cdot2-3\cdot0-0\cdot0+2\cdot1=14$，与样例（$n=5\Rightarrow14$）一致。这个数列接下来是 $1,1,0,0,2,14,90,646,\dots$

因为这个递推的系数是关于 $n$ 的简单函数（并非系数固定的常系数线性递推——系数随 $n$ 增长），所以不能用矩阵快速幂加速，只能从边界值开始正向递推到 $n$；但这本身就只是 $O(n)$，$n\le1000$ 时已经足够快。

## Complexity / 复杂度

$O(n)$ time, $O(n)$ memory (could be reduced to $O(1)$ with four rolling variables, but $O(n)$ is already fast enough for $n\le1000$).

时间 $O(n)$，空间 $O(n)$（其实可以用四个滚动变量降到 $O(1)$，但 $n\le1000$ 时 $O(n)$ 已经足够快）。
