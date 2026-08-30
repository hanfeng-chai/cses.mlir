# 329 - Raab Game II

## Problem / 题目

Two players each hold cards $1,\dots,n$. On every turn both players play one (still-unplayed) card of their choice; whoever plays the higher card scores a point (equal cards score nobody). Given $n$ and target scores $a,b$, count the number of distinct games (sequences of $n$ turns) in which the first player ends with $a$ points and the second with $b$ points, modulo $10^9+7$. Multiple independent test cases.

两个玩家各持有卡牌 $1,\dots,n$。每一轮双方各出一张（尚未出过的）牌，出牌较大的一方得一分（相等则谁都不得分）。给定 $n$ 与目标比分 $a,b$，求恰好以这个比分结束的不同对局（$n$ 轮出牌顺序）个数，对 $10^9+7$ 取模。多组独立测试数据。

## Idea / 思路

**Reduce a game to one permutation.** Fix player 1's turn order — say they play card $v$ on some turn; then player 2's card on that same turn is some value, and this pairing defines a permutation $\sigma$ of $\{1,\dots,n\}$: "$\sigma(v)$ = the card player 2 plays in the same turn player 1 plays $v$". For a *fixed* $\sigma$, every choice of player 1's own turn order (there are $n!$ of them) gives a different, valid game with the *same* $\sigma$ (player 2's turn order is then forced: play $\sigma(v)$ whenever player 1 plays $v$). So

$$\#\text{games}(n,a,b)=n!\cdot\#\{\sigma : \#\{v:v>\sigma(v)\}=a,\ \#\{v:\sigma(v)>v\}=b\}.$$

The remaining $n-a-b$ positions of $\sigma$ must be fixed points ($\sigma(v)=v$, a tie). Choosing *which* $a+b$ values are not fixed points, and how the derangement-like part behaves, only depends on the relative order of the chosen values (not which specific numbers they are), so if $m=a+b$:

$$\#\{\sigma\}=\binom{n}{m}\cdot D(m,b),$$

where $D(m,b)$ = number of permutations of $\{1,\dots,m\}$ with **no fixed points** and exactly $b$ *excedances* ($\sigma(v)>v$; the other $m-b$ non-fixed positions are automatically *deficiencies*, $\sigma(v)<v$).

**Compute $D(m,b)$ from Eulerian numbers.** Permutations of size $m$ with exactly $j$ excedances (with fixed points *allowed*) are counted by the classical Eulerian number $A(m,j)$ — excedances have exactly the same distribution as descents, both given by the Eulerian triangle
$$A(m,d)=(d+1)A(m-1,d)+(m-d)A(m-1,d-1),\qquad A(1,0)=1.$$
Splitting any size-$m$ permutation by *which* subset of positions are fixed points (size $f$, contributing $0$ to the excedance count) and requiring the rest to be fixed-point-free with the same $j$ excedances gives $A(m,j)=\sum_{f=0}^m\binom{m}{f}D(m-f,j)$ — a binomial transform, which inverts to

$$D(m,j)=\sum_{f=0}^{m}(-1)^f\binom{m}{f}A(m-f,j).$$

The whole triangle $A(\cdot,\cdot)$ is precomputed once up to the largest $n$ across all queries; each query then evaluates the inversion sum directly.

*Sanity check:* $n=3,a=1,b=2$: $D(3,2)=1$ (only permutation $(2,3,1)$ has $2$ excedances among the two derangements of size $3$), so games $=3!\cdot\binom33\cdot1=6$ — matches the sample. $n=5,a=2,b=2$: $D(4,2)=7$, games $=5!\cdot\binom54\cdot7=120\cdot5\cdot7=4200$ — matches.

**把一局比赛化为一个置换。** 固定玩家 1 的出牌顺序——设某轮玩家 1 出牌 $v$，玩家 2 同一轮出的牌就定义了一个置换 $\sigma$："$\sigma(v)$ = 玩家 1 出 $v$ 的那一轮，玩家 2 出的牌"。对于*固定*的 $\sigma$，玩家 1 自己的出牌顺序任选（$n!$ 种）都能得到一局不同、但 $\sigma$ 相同的合法对局（玩家 2 的出牌顺序随之被迫确定：玩家 1 出 $v$ 时玩家 2 必须出 $\sigma(v)$）。所以

$$\#\text{对局}(n,a,b)=n!\cdot\#\{\sigma : \#\{v:v>\sigma(v)\}=a,\ \#\{v:\sigma(v)>v\}=b\}。$$

$\sigma$ 中剩下 $n-a-b$ 个位置必须是不动点（$\sigma(v)=v$，平局）。选择*哪* $a+b$ 个数值不是不动点、以及剩下部分的错位结构，只取决于所选数值的相对大小关系（与具体是哪些数无关），所以设 $m=a+b$：

$$\#\{\sigma\}=\binom{n}{m}\cdot D(m,b)，$$

其中 $D(m,b)$ 是 $\{1,\dots,m\}$ 的**无不动点**、恰有 $b$ 个"超出"位置（*excedance*，$\sigma(v)>v$）的排列数（其余 $m-b$ 个非不动点位置自动是"亏缺"位置，$\sigma(v)<v$）。

**用欧拉数求 $D(m,b)$。** 大小为 $m$、恰有 $j$ 个 excedance（允许有不动点）的排列数，正是经典的欧拉数 $A(m,j)$——excedance 与 descent 的分布完全相同，都由欧拉三角给出：
$$A(m,d)=(d+1)A(m-1,d)+(m-d)A(m-1,d-1),\qquad A(1,0)=1。$$
把任意大小为 $m$ 的排列按"哪些位置是不动点"（大小为 $f$，对 excedance 计数贡献 $0$）分类，要求剩下部分无不动点且 excedance 数同为 $j$，就得到 $A(m,j)=\sum_{f=0}^m\binom{m}{f}D(m-f,j)$——一个二项变换，其反演为

$$D(m,j)=\sum_{f=0}^{m}(-1)^f\binom{m}{f}A(m-f,j)。$$

整张欧拉三角 $A(\cdot,\cdot)$ 只需对所有测试数据中最大的 $n$ 预处理一次；每个询问直接套用反演公式求和。

*验证：* $n=3,a=1,b=2$：$D(3,2)=1$（大小 $3$ 的两个错位排列中，只有 $(2,3,1)$ 恰有 $2$ 个 excedance），对局数 $=3!\cdot\binom33\cdot1=6$，与样例一致。$n=5,a=2,b=2$：$D(4,2)=7$，对局数 $=5!\cdot\binom54\cdot7=120\cdot5\cdot7=4200$，与样例一致。

## Complexity / 复杂度

Building the Eulerian triangle up to $N=\max n_i$ costs $O(N^2)$ time and memory. Each query evaluates an $O(n)$ inversion sum. With $N\le5000$ and $t\le1000$ this is about $2.5\times10^7+5\times10^6$ operations.

构造到 $N=\max n_i$ 的欧拉三角，时间和空间均为 $O(N^2)$。每个询问求值一次 $O(n)$ 的反演和。$N\le5000,\ t\le1000$ 时约 $2.5\times10^7+5\times10^6$ 次操作。
