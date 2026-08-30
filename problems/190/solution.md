# 190 - Inversion Probability

## Problem / 题目
Each $x_i$ is an independent uniform integer in $[1,r_i]$. Print the expected number of inversions, rounded to six decimals (ties to even).

每个 $x_i$ 独立取 $[1,r_i]$ 上的均匀整数。输出期望的逆序对数，保留六位小数（半值向偶舍入）。

## Idea / 思路
By linearity, $E[\text{inv}]=\sum_{a<b}\Pr[x_a>x_b]$, and for independent uniforms on $[1,m]$ and $[1,q]$, $\Pr[x_a>x_b]=\dfrac{1}{mq}\sum_{u=1}^{m}\min(u-1,q)$, a closed-form fraction. To match the required round-half-to-even at six decimals exactly (some true values are exact halves like $\dots955$), the sum is accumulated in exact rational form: a common denominator $D$ divisible by every $mq$ ($D=2^{12}3^{8}5^{4}7^{4}\prod_{11\le p\le 97}p^2$) using a small big-integer, then the rounded value $\lfloor\text{value}\cdot10^6\rceil$ is found by binary search with banker's rounding.

由线性性 $E[\text{inv}]=\sum_{a<b}\Pr[x_a>x_b]$，且对 $[1,m]$、$[1,q]$ 上的独立均匀变量 $\Pr[x_a>x_b]=\dfrac{1}{mq}\sum_{u=1}^{m}\min(u-1,q)$，为闭式分数。为精确满足六位小数的「半值向偶」（部分真值恰为半值，如 $\dots955$），用精确有理数累加：取能被所有 $mq$ 整除的公分母 $D=2^{12}3^{8}5^{4}7^{4}\prod_{11\le p\le 97}p^2$（小型大整数实现），再用二分配合银行家舍入求 $\lfloor\text{value}\cdot10^6\rceil$。

## Complexity / 复杂度
$O(n^2)$ pair terms plus $O(\log)$ big-integer rounding. $O(n^2)$ 个配对项，加 $O(\log)$ 的大整数舍入。
