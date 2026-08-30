# 002 - Missing Number

## Problem / 题目

We are given all numbers from $1$ to $n$ except one, in arbitrary order, and we must find the single missing number.

题目给出 $1$ 到 $n$ 之间除了某一个以外的所有数字（顺序任意），我们需要找出那个唯一缺失的数。

## Idea / 思路

The sum of all integers from $1$ to $n$ is $\frac{n(n+1)}{2}$. If we subtract the sum of the numbers that actually appear, what remains is exactly the missing number. This avoids sorting or extra memory and only needs a single pass.

从 $1$ 到 $n$ 的所有整数之和是 $\frac{n(n+1)}{2}$。如果再减去实际出现的那些数字之和，剩下的正好就是缺失的数。这种方法不需要排序，也不需要额外内存，只要扫描一遍即可。

## Watch out / 注意

With $n$ up to $2 \cdot 10^5$, the full sum reaches about $2 \cdot 10^{10}$, which overflows a 32-bit integer. We therefore accumulate in a `long long`.

当 $n$ 最大为 $2 \cdot 10^5$ 时，总和约为 $2 \cdot 10^{10}$，会让 32 位整数溢出。因此我们用 `long long` 来累加。

## Complexity / 复杂度

A single linear pass over the input: $O(n)$ time and $O(1)$ extra space.

对输入做一次线性扫描：时间 $O(n)$，额外空间 $O(1)$。
