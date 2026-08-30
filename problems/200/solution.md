# 200 - Finding Periods

## Problem / 题目
A period is a prefix length $p$ such that repeating that prefix generates the whole string (the last repetition may be partial). Print all period lengths in increasing order.

周期是一个前缀长度 $p$，重复该前缀可生成整个串（最后一次可不完整）。按递增顺序输出所有周期长度。

## Idea / 思路
A length $p$ is a period iff there is a border of length $n-p$. The border lengths come from the prefix-function failure chain (plus the empty border $0$), so the periods are $\{\,n-b\,\}$ over all border lengths $b$; in particular $b=0$ gives the trivial period $n$. Sort the results.

长度 $p$ 是周期当且仅当存在长度 $n-p$ 的边界。边界长度来自前缀函数失配链（含空边界 $0$），故周期为所有边界长度 $b$ 对应的 $\{\,n-b\,\}$；其中 $b=0$ 给出平凡周期 $n$。排序输出。

## Complexity / 复杂度
$O(n)$. $O(n)$。
