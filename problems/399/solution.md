# 399 - Coding Company

## Problem / 题目

Partition $n$ distinct coders into unlabeled teams. A team's penalty is its maximum skill minus minimum skill. Count partitions whose total penalty is at most $x$, modulo $10^9+7$.

把 $n$ 名不同程序员划分成若干无标签队伍。每个队伍的罚分是最高技能减最低技能。统计总罚分不超过 $x$ 的划分数，对 $10^9+7$ 取模。

## Idea / 思路

Sort skills $a_1\le a_2\le\dots\le a_n$ and process coders in this order. A team is **open** after its minimum-skill member has appeared but before its maximum-skill member is fixed.

Suppose $j$ teams are open between $a_{i-1}$ and $a_i$. Every open team's eventual maximum lies at or after $a_i$, while its minimum lies at or before $a_{i-1}$. Therefore crossing this skill gap adds
$$j(a_i-a_{i-1})$$
to the total penalty. This “integrate the number of open intervals over gaps” identity counts each team's maximum-minus-minimum exactly once.

Let `dp[j][c]` be the number of ways after processing a prefix, with $j$ open teams and accumulated penalty $c$. Before placing the next coder, shift cost by $j\cdot gap$. Then the coder has four conceptual choices:

1. form a singleton closed team: $j\to j$, one way;
2. join one of the $j$ open teams and leave it open: $j\to j$, $j$ ways;
3. start a new open team: $j\to j+1$, one way;
4. join and close one of the $j$ open teams: $j\to j-1$, $j$ ways.

Combining the first two gives transition multiplier $j+1$ for staying at $j$:
$$next[j][c']\mathrel{+}=dp[j][c](j+1),$$
$$next[j+1][c']\mathrel{+}=dp[j][c],$$
$$next[j-1][c']\mathrel{+}=dp[j][c]j.$$

At the end, every team must be closed, so sum `dp[0][c]` for $0\le c\le x$.

Why are unlabeled partitions counted once? In sorted processing order, every team has a unique first member (opening event) and unique last member (closing event); intermediate members uniquely choose that existing open team. Team identities are their already processed member sets, so the $j$ choices are genuine and no external team labels are introduced.

A tempting but incorrect approach is to assume teams are contiguous blocks in sorted order. Teams may interleave: for skills $1,2,3$, team $\{1,3\}$ and singleton $\{2\}$ is valid but not representable by contiguous cuts. The open-team state handles exactly such partitions.

将技能排序为 $a_1\le a_2\le\dots\le a_n$ 并按此顺序处理。某个队伍在其最低技能成员已出现、最高技能成员尚未确定时称为**开放队伍**。

若 $a_{i-1}$ 与 $a_i$ 之间有 $j$ 个开放队伍，则这些队伍的最大值都在 $a_i$ 或之后，最小值都在 $a_{i-1}$ 或之前。跨过该技能差会给总罚分增加
$$j(a_i-a_{i-1})。$$
这相当于在技能轴上对“开放区间数量”积分，会把每个队伍的最大值减最小值恰好计算一次。

设 `dp[j][c]` 为处理某个前缀后，有 $j$ 个开放队伍、累计罚分为 $c$ 的方案数。放置下一个程序员前，先把代价增加 $j\cdot gap$。随后该程序员有四种概念选择：

1. 独自形成并立即关闭一个队伍：$j\to j$，1种；
2. 加入 $j$ 个开放队伍之一并保持开放：$j\to j$，$j$ 种；
3. 开启一个新队伍：$j\to j+1$，1种；
4. 加入并关闭 $j$ 个开放队伍之一：$j\to j-1$，$j$ 种。

前两种合并为停留在 $j$ 的系数 $j+1$。最后所有队伍都必须关闭，因此累加 `dp[0][c]`，其中 $0\le c\le x$。

为什么无标签划分恰好计数一次？在固定的技能排序处理顺序中，每个队伍有唯一的第一个成员（开启事件）和最后一个成员（关闭事件），中间成员唯一地选择那个已有开放队伍。开放队伍由其已处理成员集合自然区分，不引入额外标签。

一个诱人的错误方法是认为队伍在排序后必须是连续块。事实上队伍可以交错：技能 $1,2,3$ 中，队伍 $\{1,3\}$ 与单人队 $\{2\}$ 完全合法，却不能由连续切分表示。开放队伍状态正好覆盖这种情况。

## Complexity / 复杂度

There are $O(n)$ possible open counts and $x+1$ costs for each of $n$ coders, so time is $O(n^2x)$ and rolling-array memory is $O(nx)$. With $n\le100,x\le5000$, this is about $5\cdot10^7$ states/transitions.

每个程序员对应 $O(n)$ 个开放队伍数和 $x+1$ 个代价，时间复杂度 $O(n^2x)$，滚动数组空间 $O(nx)$。在 $n\le100,x\le5000$ 时约为 $5\cdot10^7$ 级别。
