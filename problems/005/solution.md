# 005 - Permutations

## Problem / 题目

Given $n$, we must output any permutation of $1,2,\ldots,n$ such that no two adjacent elements differ by exactly $1$ (a "beautiful" permutation), or report that none exists.

给定 $n$，我们要输出 $1,2,\ldots,n$ 的任意一个排列，使得相邻两个元素的差不恰好为 $1$（即"漂亮"排列），或者报告不存在这样的排列。

## Idea / 思路

For $n=1$ the single element `1` trivially works. For $n=2$ and $n=3$ it is impossible — you can check by hand that every arrangement places two consecutive integers next to each other. For $n \ge 4$, a clean construction is to print all even numbers first, then all odd numbers: `2 4 6 ... 1 3 5 ...`. Inside the even block neighbours differ by $2$, inside the odd block they also differ by $2$, and at the junction the last even meets `1`, whose difference is at least $3$. So the construction is always valid.

当 $n=1$ 时，单个元素 `1` 显然满足条件。当 $n=2$ 和 $n=3$ 时无解——可以手动验证：任何排列都会把两个相邻的整数放在一起。当 $n \ge 4$ 时，一个简洁的构造是先输出所有偶数，再输出所有奇数：`2 4 6 ... 1 3 5 ...`。偶数块内部相邻差为 $2$，奇数块内部相邻差也为 $2$，而在交界处最后一个偶数与 `1` 相邻，差至少为 $3$。因此这个构造总是合法的。

## Multiple answers / 多解说明

This task accepts *any* valid beautiful permutation, so a token-by-token comparison against the official output would wrongly reject other correct answers. We therefore provide a problem-specific `checker.cpp` (a testlib SPJ) that verifies the output is a genuine permutation of $1..n$ with no adjacent difference of $1$, or a correct "NO SOLUTION".

本题接受*任意*合法的漂亮排列，所以逐 token 对比官方输出会错误地否定其他正确答案。为此我们提供了题目专用的 `checker.cpp`（基于 testlib 的特殊评测器），它会验证输出确实是 $1..n$ 的排列且相邻差都不为 $1$，或者验证 "NO SOLUTION" 是否正确。

## Complexity / 复杂度

We build and print the permutation in a single pass: $O(n)$ time, suitable for $n$ up to $10^6$.

我们一次构造并输出整个排列：时间 $O(n)$，适用于 $n$ 达到 $10^6$ 的规模。
