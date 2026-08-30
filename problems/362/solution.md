# 362 - Pyramid Array

## Problem / 题目

Using adjacent swaps, transform an array of $n$ distinct integers into a "pyramid" (first increasing, then decreasing — a purely increasing or purely decreasing array also counts). Find the minimum number of swaps.

用相邻交换把一个由 $n$ 个不同整数组成的数组变成"金字塔"（先增后减；纯递增或纯递减也算合法）。求最少交换次数。

## Idea / 思路

The minimum number of adjacent swaps to reach any specific target arrangement equals the number of pairwise mismatches (inversions) between the original and target order. The target pyramid is determined by choosing, for every element except the global maximum (which is fixed as the peak), a side: **L** (goes to the increasing left run) or **R** (goes to the decreasing right run).

The key simplification: for any two elements with values $x<y$, their relative order in the *target* depends **only on $x$'s side**, not $y$'s — if $x\in L$, $x$ precedes $y$ (whether $y$ is on the left, ordered by value, or on the right, entirely after the peak); if $x\in R$, $y$ precedes $x$ symmetrically. So each element's side choice only affects its pairs with *larger* elements, and different elements' choices don't interact — the total cost decomposes into an **independent choice per element**.

For element $x$ (excluding the max), let $\text{costL}(x)$ = the number of larger elements positioned to its **left** originally, and $\text{costR}(x)$ = the number of larger elements to its **right**. Assigning $x$ to $L$ costs exactly $\text{costL}(x)$ swaps (mismatches with larger elements that were originally to its left but must now follow it); assigning to $R$ costs $\text{costR}(x)$. Since $\text{costL}(x)+\text{costR}(x)$ = (total larger elements) is fixed, just pick whichever is smaller for each $x$, and sum:
$$\text{answer}=\sum_{x\ne\max}\min(\text{costL}(x),\text{costR}(x)).$$

Compute all $\text{costL}(x)$ (and hence $\text{costR}(x)$) with a single Fenwick-tree pass: insert positions in **decreasing order of value** (the global max first, since it counts as "larger" for everyone), and for each element before inserting it, query how many already-inserted (hence larger) positions lie to its left.

*Sanity check:* $[2,1,5,3]$ (max is $5$, excluded): for value $2$, $\text{costL}=0,\text{costR}=2\Rightarrow\min=0$; for value $1$, $\text{costL}=1,\text{costR}=2\Rightarrow\min=1$; for value $3$, $\text{costL}=1,\text{costR}=0\Rightarrow\min=0$. Total $=1$, matching the sample.

变到任意一个特定目标排列所需的最少相邻交换次数，等于原顺序与目标顺序之间两两不匹配（逆序对）的个数。目标金字塔由"每个非全局最大元素选一侧"决定：**L**（进入递增的左半段）或 **R**（进入递减的右半段）。

关键简化：对任意两个值 $x<y$，它们在*目标*中的相对顺序**只取决于 $x$ 选了哪一侧**，与 $y$ 无关——若 $x\in L$，则 $x$ 总在 $y$ 之前（无论 $y$ 在左边按值排序、还是在右边完全排在峰值之后）；若 $x\in R$，则对称地 $y$ 总在 $x$ 之前。于是每个元素的选择只影响它与*更大*元素之间的关系，不同元素的选择互不干扰——总代价可以**按元素独立分解**。

对元素 $x$（非最大值），设 $\text{costL}(x)$ = 原本在它**左边**、值更大的元素个数，$\text{costR}(x)$ = 原本在它**右边**、值更大的个数。把 $x$ 分到 $L$ 恰好花费 $\text{costL}(x)$ 次交换（原本在左边的那些更大元素现在必须排到它后面，产生不匹配）；分到 $R$ 花费 $\text{costR}(x)$。由于 $\text{costL}(x)+\text{costR}(x)$（值更大的元素总数）是固定的，对每个 $x$ 取较小的那个即可，再求和：
$$\text{答案}=\sum_{x\ne\max}\min(\text{costL}(x),\text{costR}(x))。$$

用一次树状数组扫描即可算出所有 $\text{costL}(x)$（从而得到 $\text{costR}(x)$）：按**值从大到小**插入位置（全局最大值最先插入，因为它对所有人都算"更大"），对每个元素在插入它之前，查询已插入（即更大）的位置中有多少在它左边。

*验证：* $[2,1,5,3]$（最大值 $5$，排除）：值 $2$ 的 $\text{costL}=0,\text{costR}=2\Rightarrow\min=0$；值 $1$ 的 $\text{costL}=1,\text{costR}=2\Rightarrow\min=1$；值 $3$ 的 $\text{costL}=1,\text{costR}=0\Rightarrow\min=0$。总和 $=1$，与样例一致。

## Complexity / 复杂度

$O(n\log n)$ time (coordinate compression + one Fenwick-tree pass), $O(n)$ memory.

时间 $O(n\log n)$（离散化 + 一次树状数组扫描），空间 $O(n)$。
