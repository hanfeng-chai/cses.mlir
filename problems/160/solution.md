# 160 - Josephus Queries

## Problem / 题目
There are $n$ children in a circle, numbered $1..n$. Starting the count, every second child is removed until none remain. For each query $(n,k)$ report the original position of the $k$-th child removed.

$n$ 个小孩围成一圈（编号 $1..n$），从头开始数，每隔一个删除一个，直到全部删完。每个询问 $(n,k)$ 求第 $k$ 个被删除的小孩的原始编号。

## Idea / 思路
The first $\lfloor n/2\rfloor$ removals are exactly the even positions $2,4,\dots$, so for $k\le\lfloor n/2\rfloor$ the answer is $2k$. Otherwise we reduce to the surviving $\lceil n/2\rceil$ odd children. After the first pass, depending on the parity of $n$ the next removal starts either at the 2nd survivor (when $n$ is even) or the 1st survivor (when $n$ is odd), giving two recursive mappings back onto the odd positions. Each call halves $n$, so a query costs $O(\log n)$.

前 $\lfloor n/2\rfloor$ 个被删的恰好是偶数位 $2,4,\dots$，因此当 $k\le\lfloor n/2\rfloor$ 时答案为 $2k$。否则问题归约到剩下的 $\lceil n/2\rceil$ 个奇数位小孩上。第一轮结束后，依据 $n$ 的奇偶性，下一次删除从第 2 个幸存者（$n$ 偶）或第 1 个幸存者（$n$ 奇）开始，对应两种把子问题答案映射回奇数位的递推。每次递归 $n$ 减半，单次询问 $O(\log n)$。

## Complexity / 复杂度
$O(\log n)$ per query. 每个询问 $O(\log n)$。
