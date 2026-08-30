# 358 - Stack Weights

## Problem / 题目

$n$ coins are known only by their relative order (coin $i$ is always heavier than coin $i-1$, exact weights unknown). Coins are pushed one at a time onto a left or right stack; after each move, decide whether we can be *sure* which stack is heavier, or `?` if the answer depends on the unknown exact weights.

$n$ 枚硬币只知道相对顺序（硬币 $i$ 总是比 $i-1$ 重，具体重量未知）。硬币逐个被放入左栈或右栈；每次放入后判断能否*确定*哪一堆更重，若取决于未知的具体重量则输出 `?`。

## Idea / 思路

Write the weights via their positive increments $w_i=d_1+d_2+\dots+d_i$ with all $d_j>0$ free. Then
$$\text{sum}(L)-\text{sum}(R)=\sum_{j=1}^n d_j\cdot\big(\underbrace{|\{i\in L : i\ge j\}|-|\{i\in R : i\ge j\}|}_{\text{bal}(j)}\big),$$
obtained by swapping the order of summation (each $w_i$ expands into a sum of $d_j$'s for $j\le i$). Since the $d_j>0$ are *completely free* positive numbers, $\text{sum}(L)>\text{sum}(R)$ for **every** valid weight assignment iff every coefficient $\text{bal}(j)\ge0$ (an adversary could otherwise blow up the one negative-coefficient $d_j$ to flip the sign); symmetrically $\text{sum}(R)>\text{sum}(L)$ always iff every $\text{bal}(j)\le0$. If neither holds, some assignment gives each side the advantage — answer `?`.

So the whole problem reduces to tracking $\text{bal}(j)=|\{i\in L:i\ge j\}|-|\{i\in R:i\ge j\}|$ for all $j=1,\dots,n$ at once, and after every move checking whether it is entirely $\ge0$, entirely $\le0$, or mixed. Placing coin $c$ into $L$ increases $\text{bal}(j)$ by $1$ for **every** $j\le c$ (a range update on $[1,c]$); placing it into $R$ decreases it by $1$ on the same range. This is exactly *range-add, global-min/max query* — a segment tree with lazy propagation, updated and queried in $O(\log n)$ per move.

*Sanity check* with the sample (coin 2→left, coin 3→right, coin 1→left): after move 1, $\text{bal}=(1,1,0)$, all $\ge0$ → `>`. After move 2, $\text{bal}=(0,0,-1)$, all $\le0$ → `<`. After move 3, $\text{bal}=(1,0,-1)$, mixed → `?` — matching the expected output exactly.

把权重写成增量形式 $w_i=d_1+d_2+\dots+d_i$，所有 $d_j>0$ 自由。于是
$$\text{sum}(L)-\text{sum}(R)=\sum_{j=1}^n d_j\cdot\big(\underbrace{|\{i\in L : i\ge j\}|-|\{i\in R : i\ge j\}|}_{\text{bal}(j)}\big)，$$
这是交换求和顺序得到的（每个 $w_i$ 展开成 $j\le i$ 的所有 $d_j$ 之和）。由于 $d_j>0$ 是*完全自由*的正数，对**所有**合法权重赋值都有 $\text{sum}(L)>\text{sum}(R)$，当且仅当每个系数 $\text{bal}(j)\ge0$（否则对手可以把唯一系数为负的那个 $d_j$ 调得极大来反转符号）；对称地，$\text{sum}(R)>\text{sum}(L)$ 恒成立当且仅当每个 $\text{bal}(j)\le0$。两者都不满足，就说明存在某种赋值让任一方占优——答案是 `?`。

于是整个问题化为：同时维护所有 $j=1,\dots,n$ 的 $\text{bal}(j)=|\{i\in L:i\ge j\}|-|\{i\in R:i\ge j\}|$，每次操作后检查它是否全体 $\ge0$、全体 $\le0$，还是正负混合。把硬币 $c$ 放入 $L$，会让**所有** $j\le c$ 的 $\text{bal}(j)$ 加 $1$（对 $[1,c]$ 做区间更新）；放入 $R$ 则在同样范围内减 $1$。这正是*区间加、查询全局最小/最大值*——用带懒标记的线段树，每次操作 $O(\log n)$ 更新与查询。

*用样例验证*（硬币2→左，硬币3→右，硬币1→左）：第一步后 $\text{bal}=(1,1,0)$，全部 $\ge0$ → `>`。第二步后 $\text{bal}=(0,0,-1)$，全部 $\le0$ → `<`。第三步后 $\text{bal}=(1,0,-1)$，正负混合 → `?`——与期望输出完全一致。

## Complexity / 复杂度

$O(n\log n)$ time (one segment-tree range update + global query per move), $O(n)$ memory.

时间 $O(n\log n)$（每次操作一次线段树区间更新 + 全局查询），空间 $O(n)$。
