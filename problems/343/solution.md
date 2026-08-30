# 343 - Distinct Values Splits

## Problem / 题目

Count the ways to split array $x_1,\dots,x_n$ into contiguous segments such that every segment consists of distinct values, modulo $10^9+7$.

求把数组 $x_1,\dots,x_n$ 切成连续段、且每一段内部元素两两不同的切割方式数，对 $10^9+7$ 取模。

## Idea / 思路

Let $dp[i]$ = number of valid ways to split the prefix $x_1,\dots,x_i$ ($dp[0]=1$, the empty prefix). To extend to $i$, the *last* segment is some $x_{j+1..i}$ that must have all-distinct values; $dp[i]=\sum_{j} dp[j]$ over every $j$ for which $[j+1,i]$ is distinct.

Maintain a sliding window: as $i$ grows, keep the smallest valid `lo` such that $x_{\text{lo}..i}$ has no repeats (a hash map tracks each value's last-seen index; whenever $x_i$ repeats a value seen at index $p\ge\text{lo}$, push `lo` to $p+1$). Then the valid $j$'s are exactly $j=\text{lo}-1,\dots,i-1$, so

$$dp[i]=\sum_{j=\text{lo}-1}^{i-1} dp[j],$$

computed in $O(1)$ with a running prefix sum $S[k]=\sum_{t=0}^{k}dp[t]$: $dp[i]=S[i-1]-S[\text{lo}-2]$ (with the usual convention that an out-of-range prefix sum is $0$). This is exactly the same "sliding window + prefix-sum DP" pattern used for counting ways to split into distinct-valued/other-constrained blocks.

设 $dp[i]$ 为把前缀 $x_1,\dots,x_i$ 切好的方式数（$dp[0]=1$，空前缀）。要扩展到 $i$，*最后一段* 一定是某个 $x_{j+1..i}$，且必须内部两两不同；$dp[i]=\sum_j dp[j]$，对所有使 $[j+1,i]$ 两两不同的 $j$ 求和。

维护一个滑动窗口：随着 $i$ 增大，保持最小的合法 `lo` 使 $x_{\text{lo}..i}$ 无重复（用哈希表记录每个值最近出现的位置；一旦 $x_i$ 与某个 $\ge\text{lo}$ 的位置 $p$ 重复，就把 `lo` 推到 $p+1$）。这样合法的 $j$ 恰好是 $j=\text{lo}-1,\dots,i-1$，于是

$$dp[i]=\sum_{j=\text{lo}-1}^{i-1} dp[j]，$$

用一个滚动前缀和 $S[k]=\sum_{t=0}^{k}dp[t]$ 就能 $O(1)$ 算出：$dp[i]=S[i-1]-S[\text{lo}-2]$（越界的前缀和按惯例取 $0$）。这正是"滑动窗口 + 前缀和 DP"这一固定套路的又一次应用。

## Complexity / 复杂度

$O(n)$ time (amortized hash map + sliding window), $O(n)$ memory.

$O(n)$ 时间（均摊哈希表 + 滑动窗口），$O(n)$ 空间。
