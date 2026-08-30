# 285 - SOS Bit Problem

## Problem / 题目
For each element $x$, count elements $y$ with (1) $x\mid y=x$, (2) $x\mathbin\&y=x$, and (3) $x\mathbin\&y\neq 0$.

对每个元素 $x$，统计满足 (1) $x\mid y=x$、(2) $x\mathbin\&y=x$、(3) $x\mathbin\&y\neq 0$ 的元素 $y$。

## Idea / 思路
Build two sum-over-subsets tables: $\text{sub}[m]$ counting elements that are submasks of $m$, and $\text{sup}[m]$ counting supermasks of $m$. Then (1) is $\text{sub}[x]$ (submasks), (2) is $\text{sup}[x]$ (supermasks), and (3) is $n$ minus the count of elements disjoint from $x$, i.e. $n-\text{sub}[\overline{x}]$.

构建两个子集和表：$\text{sub}[m]$ 统计是 $m$ 子掩码的元素数，$\text{sup}[m]$ 统计是 $m$ 超掩码的元素数。则 (1) 为 $\text{sub}[x]$（子掩码），(2) 为 $\text{sup}[x]$（超掩码），(3) 为 $n$ 减去与 $x$ 不相交的元素数，即 $n-\text{sub}[\overline{x}]$。

## Complexity / 复杂度
$O(V\log V)$ with $V=2^{20}$. $O(V\log V)$，$V=2^{20}$。
