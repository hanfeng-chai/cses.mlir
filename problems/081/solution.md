# 081 - Counting Numbers

## Problem / 题目

Count the integers in the range $[a, b]$ (up to $10^{18}$) in which no two adjacent digits are the same.

统计区间 $[a, b]$（至多 $10^{18}$）内、没有两个相邻数字相同的整数个数。

## Idea / 思路

Use digit DP. Define $f(x)$ = count of valid integers in $[0, x]$; the answer is $f(b) - f(a-1)$. Scan the decimal digits of $x$ from most significant, carrying a state $(\text{position}, \text{previous digit}, \text{tight}, \text{started})$: `tight` marks that the prefix still equals $x$'s prefix (limiting the next digit), and `started` marks whether a nonzero digit has appeared yet (so leading zeros are not treated as adjacent repeats). At each position we try digits $0\ldots\text{hi}$, skipping any digit equal to the previous one once the number has started, and memoize.

使用数位 DP。定义 $f(x)$ 为 $[0, x]$ 内合法整数的个数；答案为 $f(b) - f(a-1)$。从最高位扫描 $x$ 的十进制数字，携带状态 $(\text{位置}, \text{上一位数字}, \text{是否贴上界}, \text{是否已开始})$：`tight` 表示前缀仍等于 $x$ 的前缀（限制下一位），`started` 表示是否已出现非零数字（这样前导零不会被当作相邻重复）。每个位置尝试数字 $0\ldots\text{hi}$，在数字已开始后跳过与上一位相同的数字，并记忆化。

## Complexity / 复杂度

The state space is tiny (digits $\times$ 10 $\times$ 2 $\times$ 2), so each $f$ is $O(\text{digits} \cdot 100)$.

状态空间很小（位数 $\times$ 10 $\times$ 2 $\times$ 2），因此每次 $f$ 为 $O(\text{位数} \cdot 100)$。
