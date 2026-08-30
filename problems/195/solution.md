# 195 - Grundy's Game

## Problem / 题目
Start with one heap of $n$ coins. A move splits a heap into two non-empty heaps of *different* sizes; last to move wins. Decide the winner for $n$ up to $10^6$.

初始一堆 $n$ 枚硬币。每步把一堆分成两个大小**不同**的非空堆；最后行动者胜。对 $n$ 可达 $10^6$ 判断胜者。

## Idea / 思路
The Grundy value is $g(n)=\operatorname{mex}_{a<b,\,a+b=n} \big(g(a)\oplus g(b)\big)$, with $g(1)=g(2)=0$. The losing positions ($g(n)=0$) form the finite set $\{1,2,4,7,10,20,23,26,50,53,270,273,276,282,285,288,316,334,337,340,346,359,362,365,386,389,392,566,630,633,636,639,673,676,682,685,923,926,929,932,1222\}$ (OEIS A002188); the largest is $1222$ and none occur afterwards up to $10^6$ (verified far beyond). So the second player wins iff $n$ is in this set.

Grundy 值为 $g(n)=\operatorname{mex}_{a<b,\,a+b=n} \big(g(a)\oplus g(b)\big)$，$g(1)=g(2)=0$。必败位置（$g(n)=0$）构成有限集 $\{1,2,4,7,10,20,23,26,50,53,270,\dots,1222\}$（OEIS A002188）；最大为 $1222$，其后直到 $10^6$ 再无零点（已验证远超此范围）。故后手胜当且仅当 $n$ 在此集合中。

## Complexity / 复杂度
$O(1)$ per query (table lookup). 每询问 $O(1)$（查表）。
