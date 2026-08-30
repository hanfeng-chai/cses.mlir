# 372 - Bouncing Ball Cycle

## Problem / 题目

Same bouncing-ball setup as problem 371. Find the number of steps until the ball first returns to its starting cell, and the number of distinct cells it visits during that time.

弹跳球的设定与第 371 题相同。求球第一次回到起点所需的步数，以及这段时间内经过的不同格子数。

## Idea / 思路

**Period.** The row coordinate has period $2a$ ($a=n-1$), the column period $2b$ ($b=m-1$). The ball is back at the start exactly when *both* coordinates simultaneously complete a whole number of periods, i.e. after $\operatorname{lcm}(2a,2b)=2\cdot\operatorname{lcm}(a,b)$ steps.

**Distinct cells — the hard part.** Let $g=\gcd(a,b)$, $P=2\operatorname{lcm}(a,b)=2ab/g$. Represent the row's "phase" as $u=k\bmod 2a$ and the column's as $v=k\bmod 2b$; by CRT, $k$ ranges over exactly the pairs with $u\equiv v\pmod{2g}$. For an **interior** target cell $(r,c)$ ($0<r<a,\ 0<c<b$), its two possible row-phases are $\{r,2a-r\}$ and its two column-phases are $\{c,2b-c\}$; working out which of the $4$ combinations satisfy the CRT congruence shows the cell is reachable exactly when $r\equiv c\pmod{2g}$ **or** $r\equiv -c\pmod{2g}$ (a clean inclusion–exclusion count, evaluated with a divisor-block trick: loop over residues mod $2g$ if $2g$ is small, or over the handful of diagonal offsets otherwise — whichever is cheaper, bounding the work by $O(\sqrt{a+b})$).

**Boundary cells** ($r\in\{0,a\}$ or $c\in\{0,b\}$) need separate, careful counting: fixing $u=0$ or $u=a$, the reachable column phases $v\equiv u\pmod{2g}$ form an arithmetic progression of $b/g$ values, and folding via the column's own reflection symmetry collapses them to $1+\lfloor (b/g)/2\rfloor$ or $\lceil (b/g)/2\rceil$ distinct columns depending on whether $u\bmod 2g$ is $0$ or $g$ — derived from a small "involution on indices" argument and double-checked against a brute-force enumeration over hundreds of $(a,b)$ pairs (including the tricky non-coprime cases) before being trusted.

*Sanity check:* $(n,m)=(3,4)$ ($a=2,b=3,g=1$): period $=2\cdot6=12$✓; distinct cells (interior + all 4 boundary contributions) $=6$✓, matching the sample. The initially-tempting simpler closed form $(ab+a+b+g)/(2g)$ works when $\gcd(a,b)=1$ but is **wrong** whenever $a,b$ share a common factor (e.g. $a=b=2$ gives $2.5$, not even an integer) — caught by brute-force stress testing before submission.

**周期。** 行坐标周期为 $2a$（$a=n-1$），列坐标周期为 $2b$（$b=m-1$）。球回到起点，恰好发生在两个坐标*同时*走完整数个周期的时刻，即 $\operatorname{lcm}(2a,2b)=2\cdot\operatorname{lcm}(a,b)$ 步之后。

**不同格子数——难点所在。** 设 $g=\gcd(a,b)$，$P=2\operatorname{lcm}(a,b)=2ab/g$。把行的"相位"记为 $u=k\bmod 2a$，列的记为 $v=k\bmod 2b$；由中国剩余定理，$k$ 恰好取遍满足 $u\equiv v\pmod{2g}$ 的所有配对。对**内部**目标格子 $(r,c)$（$0<r<a,\ 0<c<b$），它的两个可能行相位是 $\{r,2a-r\}$，两个列相位是 $\{c,2b-c\}$；逐一检查这 $4$ 种组合哪些满足 CRT 同余条件，可以推出该格可达，恰好当 $r\equiv c\pmod{2g}$ **或** $r\equiv -c\pmod{2g}$（用容斥清晰计数，配合"除数分块"技巧求值：若 $2g$ 较小就枚举模 $2g$ 的余数，否则枚举为数不多的对角线偏移量——取更便宜的一种，把代价控制在 $O(\sqrt{a+b})$）。

**边界格子**（$r\in\{0,a\}$ 或 $c\in\{0,b\}$）需要单独、仔细地计数：固定 $u=0$ 或 $u=a$，满足 $v\equiv u\pmod{2g}$ 的可达列相位构成一个等差数列，共 $b/g$ 个值，再利用列自身的反射对称性把它们折叠，得到 $1+\lfloor (b/g)/2\rfloor$ 或 $\lceil (b/g)/2\rceil$ 个不同列——具体是哪个取决于 $u\bmod 2g$ 是 $0$ 还是 $g$。这是从一个小型的"下标上的对合"论证推出的，并在提交前用几百组 $(a,b)$（特别包含 $\gcd$ 不为 $1$ 的棘手情形）暴力验证过。

*验证：* $(n,m)=(3,4)$（$a=2,b=3,g=1$）：周期 $=2\cdot6=12$✓；不同格子数（内部+四类边界之和）$=6$✓，与样例一致。一开始看似诱人的简化封闭式 $(ab+a+b+g)/(2g)$，在 $\gcd(a,b)=1$ 时凑巧成立，但只要 $a,b$ 有公因子就**错**（例如 $a=b=2$ 会得到 $2.5$，甚至不是整数）——这是提交前用暴力压力测试才发现的。

## Complexity / 复杂度

$O(\sqrt{a+b})$ per test case for the interior count (divisor-block trick), $O(1)$ for the period and boundary terms. With $t\le1000$ this is fast.

每组数据内部计数用除数分块技巧 $O(\sqrt{a+b})$，周期与边界项 $O(1)$。$t\le1000$ 时运行很快。
