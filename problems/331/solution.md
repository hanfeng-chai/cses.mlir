# 331 - Permutation Inversions

## Problem / 题目

Count the permutations of $1,\dots,n$ that have exactly $k$ inversions, modulo $10^9+7$.

求 $1,\dots,n$ 的排列中恰好有 $k$ 个逆序对的排列数，对 $10^9+7$ 取模。

## Idea / 思路

Build permutations by inserting values $1,2,\dots,i$ one at a time, so that at step $i$ we insert the *current largest* value into one of the $i$ possible gaps of an already-built sequence of length $i-1$. If we insert it so that exactly $t$ elements end up to its right ($0\le t\le i-1$), that creates exactly $t$ new inversions — the new value is bigger than all $i-1$ existing ones, so it forms an inversion with each of the $t$ elements now sitting after it, and it does not change any inversion among the other $i-1$ elements (their relative order is untouched). This choice of $t$ is a bijection with the $i$ possible insertion slots, so:

$$dp[i][j]=\sum_{t=0}^{\min(i-1,j)} dp[i-1][j-t].$$

Direct evaluation of this recurrence is $O(n\cdot k)$ per row if done naively with a sliding sum, but computing it as-is for every $j$ is $O(k)$ work per $j$ (window of size up to $i$), which the code speeds up with a **prefix sum**: build `pre[j+1] = pre[j] + dp[j]`, then
$$dp_{\text{new}}[j]=\text{pre}[j+1]-\text{pre}[\max(0,\,j-i+1)],$$
i.e. the sum of a sliding window of the previous row, computed in $O(1)$ per entry after the $O(k)$ prefix-sum pass.

Base case: $dp[1][0]=1$ (the single-element permutation has $0$ inversions). Running $i$ from $2$ to $n$ and keeping only the array indexed by number of inversions $0..k$ (we never need more than $k$, since extra inversions beyond $k$ are irrelevant to the final answer) keeps memory and time under control. The final answer is $dp[n][k]$.

用"逐个插入最大值"的方式构造排列：第 $i$ 步把当前**最大**的数插入到长度为 $i-1$ 的已构造序列的 $i$ 个空隙之一。如果插入后它右边恰好有 $t$ 个元素（$0\le t\le i-1$），就恰好新增 $t$ 个逆序对——因为新数比已有的 $i-1$ 个都大，会和排在它右边的每个数构成逆序对，同时不影响原来 $i-1$ 个数之间的相对顺序（也就不改变它们内部的逆序对数）。这个"$t$"和 $i$ 个插入位置是一一对应的，所以：

$$dp[i][j]=\sum_{t=0}^{\min(i-1,j)} dp[i-1][j-t]。$$

如果对每个 $j$ 都直接求和，是滑动窗口求和，朴素做每行是 $O(k)$（窗口大小至多为 $i$），代码用**前缀和**加速：构造 `pre[j+1] = pre[j] + dp[j]`，则
$$dp_{\text{new}}[j]=\text{pre}[j+1]-\text{pre}[\max(0,\,j-i+1)]，$$
即用 $O(k)$ 的前缀和预处理后，每个位置的滑窗和只需 $O(1)$。

边界：$dp[1][0]=1$（单元素排列没有逆序对）。$i$ 从 $2$ 跑到 $n$，数组只保留逆序对数 $0..k$ 这部分（超过 $k$ 的部分对最终答案无用，无需保留），控制时间和内存。最终答案是 $dp[n][k]$。

## Complexity / 复杂度

$O(n\cdot k)$ time and $O(k)$ memory (rolling array). Since $k\le\binom{n}{2}$ and $n\le500$, this is at most about $500\times125000\approx6\times10^7$ operations.

时间 $O(n\cdot k)$，空间 $O(k)$（滚动数组）。因为 $k\le\binom{n}{2}$ 且 $n\le500$，最多约 $500\times125000\approx6\times10^7$ 次操作。
