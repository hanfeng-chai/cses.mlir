# 339 - Collecting Numbers Distribution

## Problem / 题目

(This continues the "Collecting Numbers" family.) You collect $1,2,\dots,n$ in order; each round scans the array left to right and collects as many next-consecutive numbers as it can starting from the smallest not-yet-collected number. For each $k=1,\dots,n$, count the permutations of $1,\dots,n$ that need exactly $k$ rounds, modulo $10^9+7$.

（这是"收集数字"系列的延续。）按顺序收集 $1,2,\dots,n$；每一轮从左到右扫描数组，从当前最小的未收集数字开始，尽可能多地收集后续连续的数字。对每个 $k=1,\dots,n$，求恰好需要 $k$ 轮的排列个数，对 $10^9+7$ 取模。

## Idea / 思路

Recall the key fact from the base "Collecting Numbers" problem: if $\text{pos}(v)$ is the index of value $v$ in the permutation, then a new round is forced to start exactly when $\text{pos}(v+1)<\text{pos}(v)$ — i.e. the number of rounds is $1+\#\{v : \text{pos}(v+1)<\text{pos}(v)\}$, which is exactly $1$ plus the number of **descents** of the sequence $\text{pos}(1),\text{pos}(2),\dots,\text{pos}(n)$.

As the permutation ranges over all $n!$ possibilities, $\text{pos}(1),\dots,\text{pos}(n)$ also ranges over all $n!$ permutations (it is just a relabeling), so the number of permutations with exactly $d$ descents is precisely the **Eulerian number** $A(n,d)$. Hence the answer for $k$ rounds is $A(n,k-1)$.

Eulerian numbers satisfy the standard triangle recurrence (built by inserting the new largest element $n$ into a permutation of $n-1$ elements at one of $n$ possible gaps): inserting right after an existing descent or at the very front does not create a new descent as often as inserting elsewhere, giving
$$A(n,d)=(d+1)\,A(n-1,d)+(n-d)\,A(n-1,d-1),$$
with $A(1,0)=1$. The code builds this triangle row by row up to row $n$, then outputs $A(n,0),A(n,1),\dots,A(n,n-1)$ as the answers for $k=1,\dots,n$.

*Sanity check ($n=3$):* the Eulerian numbers for $n=3$ are $A(3,0)=1,\ A(3,1)=4,\ A(3,2)=1$ — exactly the sample output $1,4,1$.

回顾"收集数字"基础题的关键结论：若 $\text{pos}(v)$ 是数值 $v$ 在排列中的下标，则恰好在 $\text{pos}(v+1)<\text{pos}(v)$ 时会被迫开启新一轮——也就是说轮数 $=1+\#\{v:\text{pos}(v+1)<\text{pos}(v)\}$，恰好是序列 $\text{pos}(1),\text{pos}(2),\dots,\text{pos}(n)$ 的**下降**（descent）个数加 $1$。

当排列取遍全部 $n!$ 种可能时，$\text{pos}(1),\dots,\text{pos}(n)$ 也恰好取遍全部 $n!$ 种排列（只是重新贴标签），所以恰有 $d$ 个下降的排列数正是**欧拉数** $A(n,d)$。因此恰需 $k$ 轮的答案就是 $A(n,k-1)$。

欧拉数满足标准的三角递推（把新的最大元素 $n$ 插入到 $n-1$ 元排列的 $n$ 个空隙之一）：插在已有下降之后、或插在最前面，不像插在其它位置那样容易产生新的下降，由此得到
$$A(n,d)=(d+1)\,A(n-1,d)+(n-d)\,A(n-1,d-1)，$$
边界 $A(1,0)=1$。代码逐行构造这个三角形直到第 $n$ 行，然后输出 $A(n,0),A(n,1),\dots,A(n,n-1)$ 作为 $k=1,\dots,n$ 的答案。

*验证（$n=3$）：* $n=3$ 的欧拉数为 $A(3,0)=1,\ A(3,1)=4,\ A(3,2)=1$——恰好就是样例输出 $1,4,1$。

## Complexity / 复杂度

Building the Eulerian triangle row by row up to row $n$ costs $O(n^2)$ time and can be done with $O(n)$ memory (two rolling rows). With $n\le5000$ this is about $2.5\times10^7$ operations.

逐行构造欧拉三角到第 $n$ 行，时间 $O(n^2)$，可用 $O(n)$ 内存（两行滚动数组）。$n\le5000$ 时约 $2.5\times10^7$ 次操作。
