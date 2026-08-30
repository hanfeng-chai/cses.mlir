# 373 - Knight Moves Queries

## Problem / 题目

For many query points $(x,y)$, find the minimum number of knight moves needed to reach $(1,1)$, where the board occupies all of $x,y\ge1$ (unbounded above).

对多个查询点 $(x,y)$，求骑士跳到 $(1,1)$ 所需的最少步数，棋盘覆盖所有 $x,y\ge1$（无上界）。

## Idea / 思路

On a truly *infinite* (unbounded in every direction) board, the minimum knight distance between two points a known distance $(dx,dy)$ apart ($dx\ge dy\ge0$) has a classical closed form, derived from the fact that on average each move advances $(dx,dy)$ by about $(1.5,1.5)$ in the "aligned" direction: with $\delta=dx-dy$,
$$\text{dist}=\begin{cases}3,&(dx,dy)=(1,0)\\4,&(dx,dy)=(2,2)\\\delta-2\left\lfloor\dfrac{\delta-dy}{3}\right\rfloor,&dy>\delta\\\delta-2\left\lfloor\dfrac{\delta-dy}{4}\right\rfloor,&dy\le\delta\end{cases}$$
(the two named special cases don't fit the general pattern and must be checked first). This formula was validated against a brute-force BFS for all small $(dx,dy)$ before use — and, critically, **floor** division must be used for the negative numerator that occurs in the $dy>\delta$ branch (C++'s `/` truncates toward zero, so a manual floor-division helper is needed).

**The catch.** This problem's board is *not* fully infinite — it's a quarter-plane ($x,y\ge1$), so paths that would cut through negative coordinates on a truly infinite board aren't available. Comparing a boundary-respecting BFS against the infinite-board formula for every small $(x,y)$ up to $40\times40$ turned up exactly **one** discrepancy: $(x,y)=(2,2)$, where the infinite-board shortcut (through a negative coordinate) gives $2$, but the true quarter-plane answer is $4$. Every other case matches the infinite-board formula, because $(1,1)$'s "shadow" of negative-coordinate shortcuts only affects points immediately adjacent to it. So the final solution is: apply the closed form, with a single hard-coded exception for $(x,y)=(2,2)\to4$.

在真正**无限**（各方向都无边界）的棋盘上，两点相距已知 $(dx,dy)$（$dx\ge dy\ge0$）时的最少骑士步数有一个经典封闭式，源于"平均每步大约让 $(dx,dy)$ 沿主方向前进 $(1.5,1.5)$"这一事实：设 $\delta=dx-dy$，
$$\text{距离}=\begin{cases}3,&(dx,dy)=(1,0)\\4,&(dx,dy)=(2,2)\\\delta-2\left\lfloor\dfrac{\delta-dy}{3}\right\rfloor,&dy>\delta\\\delta-2\left\lfloor\dfrac{\delta-dy}{4}\right\rfloor,&dy\le\delta\end{cases}$$
（这两个特判不符合一般规律，必须先单独检查）。这个公式在使用前，已对所有较小的 $(dx,dy)$ 用暴力 BFS 验证过——需要特别注意，$dy>\delta$ 分支里分子可能为负数，必须用**向下取整**除法（C++ 的 `/` 是向零截断，需要手写一个向下取整的辅助函数）。

**陷阱。** 本题的棋盘并不是真正无边界的——它是一个四分之一平面（$x,y\ge1$），所以在真正无限棋盘上那些会穿过负坐标的路径这里走不通。把"尊重边界的 BFS"与"无限棋盘公式"对所有 $40\times40$ 以内的小 $(x,y)$ 逐一比较，发现恰好有**一处**不一致：$(x,y)=(2,2)$，无限棋盘的捷径（借道负坐标）给出 $2$，但真正四分之一平面下的答案是 $4$。其它情形都与无限棋盘公式一致，因为 $(1,1)$ 附近"借道负坐标的捷径"的影响范围只波及紧邻它的那一个点。所以最终解法是：套用封闭式，只对 $(x,y)=(2,2)\to4$ 硬编码一个特例。

## Complexity / 复杂度

$O(1)$ per query after taking absolute differences, so $O(n)$ overall.

每次查询取绝对差后 $O(1)$，总体 $O(n)$。
