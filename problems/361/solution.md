# 361 - Two Array Average

## Problem / 题目

Given two arrays of $n$ integers, choose a nonempty prefix from *each* array so that the average of all chosen numbers together is as large as possible.

给定两个长度为 $n$ 的数组，从*每个*数组中各选一个非空前缀，使所选数字整体的平均值最大。

## Idea / 思路

We must pick $i,j\in[1,n]$ maximizing $\dfrac{PA_i+PB_j}{i+j}$ (prefix sums $PA,PB$). Since $i$ and $j$ are chosen **independently** (no interaction between the two prefixes other than both counting toward the same average), binary search directly on the answer value $V$: for a candidate $V$, ask "does there exist $i,j$ with $PA_i-Vi+PB_j-Vj\ge0$?" — and because $i,j$ are independent, the best possible left-hand side is simply $\big(\max_i(PA_i-Vi)\big)+\big(\max_j(PB_j-Vj)\big)$, computable in $O(n)$.

This quantity is a decreasing, convex function of $V$ that crosses zero exactly at the true optimal average (any $V$ below optimal makes it $\ge0$ achievable; any $V$ above makes it impossible) — so binary search on $V$ converges to the maximum average. Once $V$ has converged to (near) machine precision, recompute $\arg\max_i(PA_i-Vi)$ and $\arg\max_j(PB_j-Vj)$ at that $V$ — these are the winning prefix lengths, and since several $(i,j)$ pairs can tie for the same optimal average, this problem is graded with a $10^{-6}$-tolerance checker rather than requiring an exact match to one fixed pair.

*Sanity check:* at $V=3.5$ on the sample, $PA_i-3.5i$ peaks at $i=3$ (value $0.5$) and $PB_j-3.5j$ peaks at $j=1$ (value $-0.5$), summing to exactly $0$ — confirming $V=3.5$ is exactly the crossing point, with $(i,j)=(3,1)$ matching the sample output.

要选 $i,j\in[1,n]$ 最大化 $\dfrac{PA_i+PB_j}{i+j}$（$PA,PB$ 为前缀和）。由于 $i,j$ 是**独立**选取的（两个前缀除了都算进同一个平均值外没有其它关联），直接对答案数值 $V$ 二分：对候选 $V$，问"是否存在 $i,j$ 使 $PA_i-Vi+PB_j-Vj\ge0$？"——因为 $i,j$ 独立，左边能取到的最大值就是 $\big(\max_i(PA_i-Vi)\big)+\big(\max_j(PB_j-Vj)\big)$，$O(n)$ 可求。

这个量是 $V$ 的递减凸函数，恰好在真正的最优平均值处穿过零点（低于最优的 $V$ 都能让它 $\ge0$；高于最优的都不行）——所以对 $V$ 二分就能收敛到最大平均值。$V$ 收敛到（接近）机器精度后，在该 $V$ 下重新计算 $\arg\max_i(PA_i-Vi)$ 与 $\arg\max_j(PB_j-Vj)$——这就是获胜的前缀长度；由于可能有多组 $(i,j)$ 并列取得同样的最优平均值，本题用带 $10^{-6}$ 容差的 checker 评测，而不要求与某一组固定答案完全一致。

*验证：* 样例中 $V=3.5$ 时，$PA_i-3.5i$ 在 $i=3$ 处取峰值 $0.5$，$PB_j-3.5j$ 在 $j=1$ 处取峰值 $-0.5$，两者相加恰好为 $0$——确认 $V=3.5$ 正是交叉点，$(i,j)=(3,1)$ 与样例输出一致。

## Complexity / 复杂度

$O(n\log(\text{precision}))$ — each of the $\approx200$ binary-search iterations costs $O(n)$.

$O(n\log(\text{精度}))$——约 $200$ 次二分迭代，每次 $O(n)$。
