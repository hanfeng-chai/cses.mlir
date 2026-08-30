# 280 - K Subset Xors

## Problem / 题目
Among all $2^n$ subset xors (with multiplicity), output the $k$ smallest in increasing order.

在全部 $2^n$ 个子集异或（计重）中，按升序输出最小的 $k$ 个。

## Idea / 思路
With a linear basis of rank $r$, there are $2^r$ distinct values, each occurring exactly $2^{n-r}$ times among the $2^n$ subsets. Reduce the basis to row-echelon form sorted by leading bit; then the $i$-th smallest distinct value is the xor of the basis vectors selected by the binary digits of $i$. The $p$-th smallest overall (with multiplicity) is the distinct value at index $\lfloor p/2^{n-r}\rfloor$; when $2^{n-r}$ exceeds $k$, all $k$ answers are $0$.

设线性基秩为 $r$，则有 $2^r$ 个不同值，每个在 $2^n$ 个子集中恰出现 $2^{n-r}$ 次。把基约化为按主位排序的行最简形；则第 $i$ 小的不同值为按 $i$ 的二进制位选取基向量的异或。计重下第 $p$ 小为下标 $\lfloor p/2^{n-r}\rfloor$ 处的不同值；当 $2^{n-r}>k$ 时，$k$ 个答案全为 $0$。

## Complexity / 复杂度
$O(n\log V + k\log V)$. $O(n\log V + k\log V)$。
