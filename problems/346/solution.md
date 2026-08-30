# 346 - Multiplication Table

## Problem / 题目

Find the median element of the $n\times n$ multiplication table (the multiset $\{i\cdot j : 1\le i,j\le n\}$), for odd $n$.

求 $n\times n$ 乘法表（多重集 $\{i\cdot j : 1\le i,j\le n\}$）排序后的中间元素，$n$ 为奇数。

## Idea / 思路

This is the classic "$K$-th smallest value in a multiplication table" problem, solved by **binary search on the answer value** $V$: for any candidate $V$, count how many products $i\cdot j\le V$ without listing them, then compare that count to the target rank.

For a fixed row $i$, the values $i\cdot1, i\cdot2,\dots,i\cdot n$ are simply $i,2i,\dots,ni$, so the count of them that are $\le V$ is $\min(n,\lfloor V/i\rfloor)$. Summing over $i=1,\dots,n$ gives, in $O(n)$, the total count of table entries $\le V$. Binary search $V$ over $[1,n^2]$ for the smallest value whose count is $\ge$ the target rank $\frac{n^2+1}{2}$ (the median position, since $n^2$ is odd when $n$ is odd) — that smallest such $V$ is guaranteed to actually be *achieved* by some product (a standard property of this kind of counting binary search), so it is exactly the answer.

这是经典的"乘法表中第 $K$ 小的数"问题，用**对答案数值二分**解决：对任意候选值 $V$，不需要真的列出所有乘积，就能数出有多少个 $i\cdot j\le V$，再与目标排名比较。

固定一行 $i$，其中的值 $i\cdot1,i\cdot2,\dots,i\cdot n$ 就是 $i,2i,\dots,ni$，所以其中 $\le V$ 的个数是 $\min(n,\lfloor V/i\rfloor)$。对 $i=1,\dots,n$ 求和，就能在 $O(n)$ 内得到表中 $\le V$ 的元素总数。在 $[1,n^2]$ 上二分 $V$，找到使这个计数 $\ge$ 目标排名 $\frac{n^2+1}{2}$（因为 $n$ 为奇数时 $n^2$ 也是奇数，这就是中位数所在的排名）的最小 $V$——这个最小的 $V$ 必然真的能被某个乘积取到（这类计数二分的标准性质），因此它就是答案。

## Complexity / 复杂度

$O(n\log(n^2))=O(n\log n)$ time, $O(1)$ memory.

时间 $O(n\log(n^2))=O(n\log n)$，空间 $O(1)$。
