# 378 - Swap Round Sorting

## Problem / 题目

Sort a permutation using "swap rounds": each round may perform any number of *disjoint* pairwise swaps simultaneously. Find the minimum number of rounds and a valid sequence.

用"交换轮次"排序一个排列：每轮可以同时进行任意数量的*两两不相交*交换。求最少轮数及一个合法方案。

## Idea / 思路

One round of disjoint swaps is exactly an **involution** (a permutation equal to its own inverse — a product of disjoint transpositions, with untouched elements as fixed points). So the question "can this permutation be sorted in $r$ rounds" is exactly "can the permutation be written as a product of $r$ involutions."

Decompose the permutation into cycles (fixed points need $0$ rounds). A cycle of length $1$ needs nothing; a cycle of length $2$ **is already** an involution, so it can be resolved in a single round together with anything else. For a cycle of length $\ge3$, a classical group-theory fact guarantees it can *always* be written as a product of **exactly $2$** involutions (every permutation is conjugate to its inverse, since a cycle and its reverse have the same length) — so **2 rounds always suffice, regardless of how long the cycle is**, and $2$ is clearly necessary whenever some cycle has length $\ge3$ (one round of disjoint transpositions cannot fix a $\ge3$-cycle by itself). So the overall answer is: $0$ if the array is already sorted; $1$ if every non-trivial cycle has length exactly $2$; otherwise $2$.

**Explicit construction for a cycle of length $L\ge3$** (given as a position sequence $c_0,c_1,\dots,c_{L-1}$, where the value currently at $c_i$ belongs at $c_{i+1\bmod L}$): round 1 swaps $(c_i,\,c_{L-1-i})$ for every $i<L-1-i$ (a "fold in half"); after applying these, whatever is left out of place always pairs up perfectly into disjoint mutual swaps, which become round 2. This exact "reversal, then residual" construction was verified against a brute-force check (that it actually sorts the array using genuinely disjoint swaps) for cycle lengths $2$ through $19$ before being trusted, and it reproduces the sample's own round-1/round-2 swaps exactly.

一轮不相交的交换，正好是一个**对合**（involution，即和自身的逆相同的置换——若干不相交的对换的乘积，未被涉及的元素则是不动点）。所以"能否用 $r$ 轮排好序"，正好等价于"这个置换能否写成 $r$ 个对合的乘积"。

把置换分解成循环（不动点不需要任何轮次）。长度为 $1$ 的循环什么都不用做；长度为 $2$ 的循环**本身就是**一个对合，可以和其它内容一起在同一轮里解决。对于长度 $\ge3$ 的循环，一个经典的群论事实保证它*总能*写成恰好 **$2$ 个**对合的乘积（任何置换都与其逆共轭，因为一个循环和它反向遍历得到的循环长度相同）——所以**无论循环有多长，$2$ 轮总是够的**，而只要存在长度 $\ge3$ 的循环，$2$ 轮显然也是必要的（一轮不相交对换本身无法单独修复一个长度 $\ge3$ 的循环）。所以总答案是：数组已排好序则为 $0$；所有非平凡循环长度都恰为 $2$ 则为 $1$；否则为 $2$。

**长度 $L\ge3$ 的循环的具体构造**（给定为位置序列 $c_0,c_1,\dots,c_{L-1}$，其中当前在 $c_i$ 处的值最终要去 $c_{i+1\bmod L}$）：第 $1$ 轮对每个 $i<L-1-i$ 交换 $(c_i,\,c_{L-1-i})$（相当于"对折一半"）；执行完这些之后，剩下没归位的元素总能恰好两两配对成互相需要交换的对，这些就是第 $2$ 轮。这个"先对折、再处理残余"的构造，在使用前已经用暴力检验（确认它确实用真正互不相交的交换把数组排好序）验证了循环长度 $2$ 到 $19$ 的情形，并且它得到的第 $1$、$2$ 轮交换与样例给出的完全一致。

## Complexity / 复杂度

$O(n)$ time overall: finding cycles is $O(n)$, and each cycle's fold-and-residual construction visits each of its elements a constant number of times.

总体 $O(n)$：找循环 $O(n)$，每个循环的"对折+残余"构造对其每个元素只访问常数次。
