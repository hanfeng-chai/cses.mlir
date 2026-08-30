# 363 - Permutation Subsequence

## Problem / 题目

Given two permutations (array $a$ of $1,\dots,n$ and array $b$ of $1,\dots,m$), find their longest common subsequence, and print one example.

给定两个排列（数组 $a$ 是 $1,\dots,n$ 的排列，数组 $b$ 是 $1,\dots,m$ 的排列），求它们的最长公共子序列，并输出一个具体例子。

## Idea / 思路

LCS between two general strings is $O(nm)$ — too slow here. But since both arrays are **permutations**, every value that occurs in both (i.e. every value $\le\min(n,m)$) occurs *exactly once* in each. So a common subsequence is exactly a set of shared values chosen so that they occur in increasing **position** order in both $a$ and $b$ simultaneously — which is precisely the classic **"LCS of two permutations reduces to LIS"** trick.

Scan $a$ left to right (this fixes the order of positions in $a$ automatically); for every value $v\le m$ encountered, record $\text{posB}(v)$ — where that same value sits in $b$. This produces a sequence $T$. A common subsequence, respecting position order in $a$ by construction, additionally respects position order in $b$ exactly when the corresponding $T$-values are **increasing** — so the answer is the **longest increasing subsequence of $T$**, found in $O(n\log n)$ with the standard patience-sorting technique, tracking predecessors for reconstruction.

*Sanity check:* $a=[3,1,2,8,5,7,6,4]$, $b=[6,5,1,2,3,4]$ ($m=6$). Filtering $a$ to values $\le6$ gives $[3,1,2,5,6,4]$, and their $b$-positions give $T=[5,3,4,2,1,6]$. The LIS of $T$ is $[3,4,6]$ (at $T$-indices $1,2,5$), corresponding to $a$-values $[1,2,4]$ — length $3$, matching the sample exactly.

两个一般字符串的 LCS 是 $O(nm)$——这里太慢。但由于两个数组都是**排列**，任何在两者中都出现的值（即所有 $\le\min(n,m)$ 的值）在每个数组中都*恰好出现一次*。所以一个公共子序列，本质上就是选出一组共享的值，使它们在 $a$ 和 $b$ 中同时按位置递增出现——这正是经典的**"两个排列的 LCS 化为 LIS"**技巧。

从左到右扫描 $a$（这样天然固定了在 $a$ 中的位置顺序）；对遇到的每个满足 $v\le m$ 的值，记录 $\text{posB}(v)$——它在 $b$ 中的位置。这样得到一个序列 $T$。一个公共子序列，构造上已经满足在 $a$ 中位置递增，只需再满足在 $b$ 中位置递增——即对应的 $T$ 值**递增**——所以答案就是 $T$ 的**最长递增子序列**，用标准的耐心排序技巧 $O(n\log n)$ 求出，同时记录前驱用于还原具体序列。

*验证：* $a=[3,1,2,8,5,7,6,4]$，$b=[6,5,1,2,3,4]$（$m=6$）。把 $a$ 过滤到 $\le6$ 的值得到 $[3,1,2,5,6,4]$，取它们在 $b$ 中的位置得 $T=[5,3,4,2,1,6]$。$T$ 的 LIS 是 $[3,4,6]$（在 $T$ 的下标 $1,2,5$ 处），对应 $a$ 的值 $[1,2,4]$——长度 $3$，与样例完全一致。

## Complexity / 复杂度

$O(n\log n+m)$ time, $O(n+m)$ memory.

时间 $O(n\log n+m)$，空间 $O(n+m)$。
