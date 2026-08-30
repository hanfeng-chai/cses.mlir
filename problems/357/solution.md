# 357 - Water Containers Queries

## Problem / 题目

Same containers-and-pouring setup as problem 356, but now only decide **YES/NO** — is $x$ units in $A$ reachable at all? — for many $(a,b,x)$ triples with values up to $10^9$ (too large for the BFS/Dijkstra used in 356).

与第 356 题相同的倒水设定，但现在只需判断**是否可能**（YES/NO）让 $A$ 恰好有 $x$ 单位水，且 $a,b,x$ 可达 $10^9$（大到无法像第 356 题那样跑 BFS/Dijkstra）。

## Idea / 思路

This is the classical **two-jug water puzzle**. Every capacity must satisfy $w_1<w_2<\dots$ trivially not directly relevant here; instead, think of the invariant that the pouring operations preserve: any reachable amount in $A$ is a value obtainable by repeatedly adding/subtracting $a$ and $b$ (mod nothing — this is really just Bézout's identity in disguise, since fill/empty/pour is exactly how the extended Euclidean algorithm is *physically simulated* with two jugs). The set of values reachable in $A$ is exactly the multiples of $g=\gcd(a,b)$ that do not exceed $A$'s own capacity — i.e.

$$x\text{ is reachable in }A \iff x\le a \text{ and } g \mid x, \quad g=\gcd(a,b).$$

(Note the bound is $x\le a$ specifically — $A$'s *own* capacity — not $\max(a,b)$; a naive guess using $\max(a,b)$ is wrong, e.g. $a=1,b=18,x=7$ is unreachable in $A$ even though $7\le18=\max(a,b)$, since $A$ itself can only ever hold $0$ or $1$.) This closed form was validated here against a brute-force BFS over the small state graph on thousands of random cases before being trusted for the large-input version.

这是经典的**双壶量水问题**。倒水操作所保持的不变量，本质上就是反复对 $a,b$ 做加减——这其实正是扩展欧几里得算法用两个容器"物理模拟"出来的过程（Bézout 恒等式的具体体现）。$A$ 中能达到的水量集合，恰好是不超过 $A$ 自身容量、且是 $g=\gcd(a,b)$ 的倍数的那些值，即

$$x \text{ 在 } A \text{ 中可达} \iff x\le a \text{ 且 } g \mid x, \quad g=\gcd(a,b)。$$

（注意上界具体是 $x\le a$——$A$ *自己*的容量——而不是 $\max(a,b)$；直接猜 $\max(a,b)$ 是错的，例如 $a=1,b=18,x=7$ 在 $A$ 中不可达，尽管 $7\le18=\max(a,b)$，因为 $A$ 自身永远只能装 $0$ 或 $1$。）这个封闭公式在这里先用暴力 BFS 在小状态图上、对几千个随机用例做了验证，确认无误后才用于大数据版本。

## Complexity / 复杂度

$O(\log(\min(a,b)))$ per query for the gcd, so $O(n\log(\max\text{ value}))$ overall.

每次询问求 gcd 需 $O(\log(\min(a,b)))$，总体 $O(n\log(\max\text{值}))$。
