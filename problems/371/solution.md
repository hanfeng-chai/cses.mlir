# 371 - Bouncing Ball Steps

## Problem / 题目

A ball starts at the top-left corner of an $n\times m$ grid, moving diagonally, and reflects off the border whenever it reaches it. Find its position after $k$ steps, and how many times it has changed direction.

一个球从 $n\times m$网格的左上角出发，沿对角线方向移动，碰到边界就反弹。求经过 $k$ 步后的位置，以及方向改变的次数。

## Idea / 思路

The row coordinate and column coordinate bounce **independently** — the row only cares about hitting the top/bottom border, the column only about the left/right border. So each coordinate is a classic 1D "bouncing" (triangle-wave) sequence with period $2a$ (row, $a=n-1$) or $2b$ (column, $b=m-1$): within one period the position goes $0,1,\dots,a,\dots,1,0$. Computing `pos(k) = k mod 2a`, then reflecting (`2a - pos` if `pos > a`) gives the row directly in $O(1)$, and likewise for the column.

For the number of direction changes: the row bounces (reverses direction) exactly at steps that are multiples of $a$, so it has contributed $\lfloor k/a\rfloor$ direction changes by step $k$; similarly the column contributes $\lfloor k/b\rfloor$. But if a step is a multiple of **both** $a$ and $b$ (i.e. a multiple of $\operatorname{lcm}(a,b)$), the ball bounces off a corner — that's still just **one** direction change, not two, so it's been double-counted and must be subtracted once:
$$\text{changes}(k)=\left\lfloor\frac{k}{a}\right\rfloor+\left\lfloor\frac{k}{b}\right\rfloor-\left\lfloor\frac{k}{\operatorname{lcm}(a,b)}\right\rfloor.$$

行坐标和列坐标是**独立**反弹的——行只关心是否碰到上下边界，列只关心左右边界。所以每个坐标都是经典的一维"弹跳"（三角波）序列，周期为 $2a$（行，$a=n-1$）或 $2b$（列，$b=m-1$）：一个周期内位置走 $0,1,\dots,a,\dots,1,0$。用 `pos(k) = k mod 2a`，再做一次反射（若 `pos > a` 则取 `2a - pos`），就能 $O(1)$ 直接算出行坐标，列坐标同理。

方向改变次数：行恰好在 $a$ 的倍数步反弹（改变方向），所以到第 $k$ 步为止贡献了 $\lfloor k/a\rfloor$ 次方向改变；列同理贡献 $\lfloor k/b\rfloor$ 次。但如果某一步同时是 $a$ 和 $b$ 的倍数（即 $\operatorname{lcm}(a,b)$ 的倍数），球是撞在角上反弹——这仍然只算**一次**方向改变，不是两次，所以被重复计数了一次，需要减掉：
$$\text{方向改变}(k)=\left\lfloor\frac{k}{a}\right\rfloor+\left\lfloor\frac{k}{b}\right\rfloor-\left\lfloor\frac{k}{\operatorname{lcm}(a,b)}\right\rfloor。$$

## Complexity / 复杂度

$O(\log(\max(n,m)))$ per test case (for the gcd/lcm computation), $O(1)$ for everything else.

每组数据 $O(\log(\max(n,m)))$（求 gcd/lcm），其余均为 $O(1)$。
