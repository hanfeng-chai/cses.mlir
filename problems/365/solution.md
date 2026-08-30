# 365 - Writing Numbers

## Problem / 题目

Writing the numbers $1,2,3,\dots$ in order presses each digit key $0$–$9$ some number of times. Each key can be pressed at most $n$ times. Find the last number that can still be written.

依次写下 $1,2,3,\dots$，会按下数字键 $0$–$9$ 若干次。每个键最多能按 $n$ 次。求还能写出的最后一个数。

## Idea / 思路

The set of writable prefixes $\{1,\dots,M\}$ is exactly those $M$ for which **every** digit $0$–$9$ is used at most $n$ times among $1,\dots,M$ — and this feasibility is monotonic in $M$ (using a longer prefix never *decreases* any digit's usage count), so **binary search on $M$**.

For the feasibility check, we need `countDigit(M,d)` = how many times digit $d$ appears among $1,\dots,M$, for each of the $10$ digits. This is the classic "digit counting" technique: process each decimal place (units, tens, hundreds, …) with place value $p$; split $M$ into `higher = M/(p*10)`, `cur = (M/p)%10`, `lower = M%p`. For $d\ge1$: this place contributes digit $d$ exactly `higher*p` times from "full cycles", plus `p` more if `cur>d`, or `lower+1` more if `cur==d`. For $d=0$ the same idea applies but a full "cycle" only counts once `higher\ge1` (a leading zero doesn't count), so the full-cycle term becomes `(higher-1)*p` instead.

*Sanity check:* with $n=5$, `countDigit(12,1)` = $5$ (from `1`,`10`,`11`—twice—,`12`), exactly hitting the budget, while writing `13` would need a $6$th `1`. So $M=12$ is the last writable number, matching the sample.

可写出的前缀集合 $\{1,\dots,M\}$，恰好对应那些使 $0$–$9$ **每个**数字在 $1,\dots,M$ 中出现次数都 $\le n$ 的 $M$——并且这个可行性关于 $M$ 单调（前缀越长，任何数字的使用次数都不会*减少*），所以**对 $M$ 二分**。

可行性检查需要 `countDigit(M,d)` = 数字 $d$ 在 $1,\dots,M$ 中出现的次数，对 $10$ 个数字都要算。这是经典的"数位计数"技巧：对每个十进制位（个位、十位、百位……，位权为 $p$）处理；把 $M$ 拆成 `higher = M/(p*10)`、`cur = (M/p)%10`、`lower = M%p`。对 $d\ge1$：这一位上，"完整循环"贡献 `higher*p` 次数字 $d$，再加上：若 `cur>d` 则多 `p` 次，若 `cur==d` 则多 `lower+1` 次。对 $d=0$ 思路相同，但"完整循环"只在 `higher>=1` 时才计一次（前导零不算），所以完整循环这一项要改成 `(higher-1)*p`。

*验证：* $n=5$ 时，`countDigit(12,1)` $=5$（来自 `1`、`10`、`11`——两次——、`12`），恰好用满预算；而写 `13` 需要第 $6$ 次按 `1`。所以 $M=12$ 是最后能写出的数，与样例一致。

## Complexity / 复杂度

$O(\log M)$ per feasibility check (one pass over decimal places for each of $10$ digits), $O(\log(\text{range})\cdot\log M)$ overall for the binary search.

每次可行性检查 $O(\log M)$（对 $10$ 个数字各扫一遍十进制位），二分总体 $O(\log(\text{范围})\cdot\log M)$。
