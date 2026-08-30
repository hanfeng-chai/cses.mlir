# 383 - Programmers and Artists

## Problem / 题目

There are $n$ applicants; you must hire exactly $a$ of them as programmers (contributing their programming skill $x_i$) and exactly $b$ of them as artists (contributing their artistic skill $y_i$), with $a+b\le n$ and the rest not hired. Maximize the total skill sum.

有 $n$ 名申请者；必须恰好雇佣 $a$ 人做程序员（贡献编程技能 $x_i$）、恰好 $b$ 人做艺术家（贡献艺术技能 $y_i$），$a+b\le n$，其余不雇佣。求可获得的最大技能总和。

## Idea / 思路

**Exchange argument.** In an optimal solution, if programmer $p$ and artist $q$ satisfy $x_p-y_p < x_q-y_q$, swapping their roles changes the total by $(x_q-y_q)-(x_p-y_p)>0$ — a strict improvement, contradiction. So in *any* optimal solution, every programmer's $x_i-y_i$ is $\ge$ every artist's $x_i-y_i$.

Sort all applicants by $x_i-y_i$ descending. The exchange argument shows the programmers occupy some set of ranks, the artists occupy some (entirely later) set of ranks, and unhired people can be interspersed with either group. This means: for **some split point** $k$ ($0\le k\le n$), all programmers come from the first $k$ people in this order, and all artists come from the last $n-k$ people — but *which* $a$ of the first $k$ become programmers should be chosen to maximize $\sum x_i$ (i.e. the top $a$ by $x_i$ among the first $k$), and similarly artists are the top $b$ by $y_i$ among the last $n-k$.

**Important pitfall:** it is *tempting* (and wrong) to fix $k=a+b$ directly, i.e. "top $a$ by $x-y$ become programmers, the next $b$ become artists". Counterexample: $x=[100,1,1]$, $y=[1,100,1]$, $a=b=1$. Sorting by $x-y$ descending gives person1 ($99$), person3 ($0$), person2 ($-99$). The naive rule picks person1 as programmer ($100$) and person3 as artist ($y=1$), total $101$ — but the true optimum is person1 as programmer and person2 (ranked *last*!) as artist ($y=100$), total $200$, because person2's raw $y$-value is huge even though their $x-y$ difference is very negative. The fix is to try **every** split point $k$ (not just $k=a+b$) and, for each, take the best $a$ by $x$ from the prefix and best $b$ by $y$ from the suffix — since the prefix/suffix boundary can have "mediocre" unhired people sitting between the true programmer- and artist- ranks.

Compute, for every $k=0,\dots,n$: $\mathrm{bestP}(k)=$ sum of the top $a$ values of $x$ among the first $k$ people in this order (invalid if $k<a$), and $\mathrm{bestA}(k)=$ sum of the top $b$ values of $y$ among the last $n-k$ people (invalid if $n-k<b$). Both are computed with a size-capped min-heap swept from the left (for $\mathrm{bestP}$) and from the right (for $\mathrm{bestA}$): push the new value, and if the heap exceeds the cap ($a$ or $b$), pop the smallest — the running heap sum is exactly the sum of the top values seen so far. The answer is $\max_k \mathrm{bestP}(k)+\mathrm{bestA}(k)$.

*Verified* on the counterexample above (gives 200) and on the given sample ($a=2,b=1$, $x=[3,9,1,4]$, $y=[7,8,5,2]$: at $k=2$, $\mathrm{bestP}=9+4=13$, $\mathrm{bestA}(2)=$ top-1 $y$ among the last 2 people $=7$, total $20$, matching the expected output).

**关键交换论证。** 在最优解中，若程序员 $p$ 和艺术家 $q$ 满足 $x_p-y_p < x_q-y_q$，交换二人角色会让总和变化 $(x_q-y_q)-(x_p-y_p)>0$——严格变好，矛盾。所以在**任意**最优解中，每个程序员的 $x_i-y_i$ 都 $\ge$ 每个艺术家的 $x_i-y_i$。

按 $x_i-y_i$ 降序排序。交换论证说明程序员占据某些排名靠前的位置，艺术家占据（整体更靠后的）某些位置，未被雇佣的人可以夹在两者之间。这意味着：存在**某个分割点** $k$（$0\le k\le n$），使得所有程序员来自这个顺序下的前 $k$ 人，所有艺术家来自后 $n-k$ 人——但具体挑前 $k$ 人中的哪 $a$ 个做程序员，应该选 $x_i$ 最大的 $a$ 个；同理艺术家应该选后 $n-k$ 人中 $y_i$ 最大的 $b$ 个。

**常见陷阱：** 很容易（错误地）直接令 $k=a+b$，即"按 $x-y$ 排序后前 $a$ 个当程序员、接下来 $b$ 个当艺术家"。反例：$x=[100,1,1]$，$y=[1,100,1]$，$a=b=1$。按 $x-y$ 降序排序得到 person1（$99$）、person3（$0$）、person2（$-99$）。朴素规则会选 person1 当程序员（$100$），person3 当艺术家（$y=1$），总和 $101$——但真正的最优解是 person1 当程序员、person2（排名**最后**！）当艺术家（$y=100$），总和 $200$，因为 person2 的原始 $y$ 值很大，尽管其 $x-y$ 差值很负。修正方法是尝试**所有**分割点 $k$（不只是 $k=a+b$），对每个 $k$ 分别取前缀中 $x$ 最大的 $a$ 个、后缀中 $y$ 最大的 $b$ 个——因为分界处可能夹着"两边都平庸"的未雇佣者。

对每个 $k=0,\dots,n$ 计算：$\mathrm{bestP}(k)=$ 该顺序下前 $k$ 人中 $x$ 值最大的 $a$ 个之和（若 $k<a$ 则无效），$\mathrm{bestA}(k)=$ 后 $n-k$ 人中 $y$ 值最大的 $b$ 个之和（若 $n-k<b$ 则无效）。两者都用一个大小上限为 $a$（或 $b$）的小顶堆从左（求 $\mathrm{bestP}$）和从右（求 $\mathrm{bestA}$）扫描得到：push 新值，若堆大小超过上限则弹出最小值，堆中元素之和即为目前见过的最大若干值之和。答案为 $\max_k \mathrm{bestP}(k)+\mathrm{bestA}(k)$。

已在上述反例（得到200）和给定样例（$a=2,b=1$，$x=[3,9,1,4]$，$y=[7,8,5,2]$：$k=2$ 时 $\mathrm{bestP}=9+4=13$，后2人中 $y$ 最大的1个是 $7$，总和 $20$，与期望输出一致）上验证过。

## Complexity / 复杂度

Sorting is $O(n\log n)$; the two heap sweeps are $O(n\log a)$ and $O(n\log b)$. Overall $O(n\log n)$ for $n\le 2\times 10^5$.

排序 $O(n\log n)$；两次堆扫描各为 $O(n\log a)$、$O(n\log b)$。整体 $O(n\log n)$，$n\le 2\times 10^5$ 内轻松通过。
