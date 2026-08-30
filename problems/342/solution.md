# 342 - Distinct Values Sum

## Problem / 题目

For an array $x_1,\dots,x_n$, let $d(a,b)$ be the number of distinct values in $x_a,\dots,x_b$. Compute $\sum_{a=1}^n\sum_{b=a}^n d(a,b)$.

给定数组 $x_1,\dots,x_n$，设 $d(a,b)$ 为子数组 $x_a,\dots,x_b$ 中不同值的个数。求 $\sum_{a=1}^n\sum_{b=a}^n d(a,b)$。

## Idea / 思路

Swap the order of summation: instead of summing $d(a,b)$ over subarrays, sum, for each *position* $i$, how many subarrays $[a,b]$ count $x_i$ towards their distinct total. Position $i$ contributes to $d(a,b)$ exactly when $i$ is the **first** occurrence of its value inside $[a,b]$ — i.e. $a$ must be strictly after the previous occurrence of $x_i$ (call its index $\text{prev}(i)$, or $0$/"before the array" if there is none) and $a\le i\le b$.

So for fixed $i$: valid $a$ ranges over $(\text{prev}(i), i]$ — that's $i-\text{prev}(i)$ choices — and valid $b$ ranges over $[i,n]$ — that's $n-i+1$ choices. Every such $(a,b)$ pair counts $x_i$ exactly once towards $d(a,b)$, and every occurrence of $x_i$ being "first in its window" is captured this way, so

$$\text{answer}=\sum_{i=1}^n (i-\text{prev}(i))\cdot(n-i+1).$$

`prev(i)` is just "the last index before $i$ with the same value", tracked with a hash map in one linear pass.

交换求和顺序：不按子数组求和 $d(a,b)$，而是对每个**位置** $i$，数有多少个子数组 $[a,b]$ 会把 $x_i$ 计入它们的"不同值"总数。位置 $i$ 对 $d(a,b)$ 有贡献，恰好发生在 $i$ 是 $[a,b]$ 内它这个值的**第一次**出现时——也就是说 $a$ 必须严格晚于 $x_i$ 的上一次出现位置（记为 $\text{prev}(i)$，不存在则视为 $0$/"数组开始之前"），且 $a\le i\le b$。

固定 $i$：合法的 $a$ 取值范围是 $(\text{prev}(i), i]$——共 $i-\text{prev}(i)$ 种；合法的 $b$ 取值范围是 $[i,n]$——共 $n-i+1$ 种。每一个这样的 $(a,b)$ 都恰好把 $x_i$ 计入 $d(a,b)$ 一次，且 $x_i$ 每一次"在某个窗口里第一次出现"都被这样统计到了，所以

$$\text{答案}=\sum_{i=1}^n (i-\text{prev}(i))\cdot(n-i+1)。$$

`prev(i)` 就是"$i$ 之前最近一个相同值的位置"，用哈希表一次线性扫描即可维护。

## Complexity / 复杂度

$O(n)$ time (amortized hash map operations), $O(n)$ memory.

$O(n)$ 时间（均摊哈希表操作），$O(n)$ 空间。
