# 287 - Inverse Inversions

## Problem / 题目
Construct a permutation of $1..n$ ($n\le 10^6$) having exactly $k$ inversions.

构造一个恰有 $k$ 个逆序对的 $1..n$（$n\le 10^6$）排列。

## Idea / 思路
Greedily place values. While placing into a prefix, the largest remaining value contributes $m-1$ inversions where $m$ is the number of remaining values; place it whenever $k\ge m-1$ and subtract. Once $k<m-1$, place the value $k+1$ (which creates exactly $k$ inversions because $k$ smaller values follow it) and then output the rest in increasing order, contributing no further inversions.

贪心放置值。放入前缀时，剩余最大值会贡献 $m-1$ 个逆序对（$m$ 为剩余值数）；当 $k\ge m-1$ 时放它并相减。一旦 $k<m-1$，放值 $k+1$（它后面恰有 $k$ 个更小值，产生 $k$ 个逆序对），其余按升序输出不再产生逆序对。

## Multi-solution / 多解
Any permutation with $k$ inversions is accepted; a custom checker verifies the permutation and counts its inversions.

任意有 $k$ 个逆序对的排列均可；checker 验证排列并统计逆序对数。

## Complexity / 复杂度
$O(n)$. $O(n)$。
