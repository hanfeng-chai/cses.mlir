# 384 - Removing Digits II

## Problem / 题目

Starting from $n\le10^{18}$, each move subtracts a decimal digit that appears in the current number. Find the minimum number of moves to reach zero.

从 $n\le10^{18}$ 开始，每步减去当前数字十进制表示中出现的某一位，求变成0的最少步数。

## Idea / 思路

For this operation, subtracting the largest currently present digit is optimal. This can be shown by the monotonicity of the value function: a larger allowed subtraction reaches a no-harder smaller state, and the decimal borrow structure does not create an advantage that compensates for choosing a smaller digit first. As a concrete verification, the greedy choice was compared with the exact recurrence
$$dp[x]=1+\min_{d\text{ is a nonzero digit of }x}dp[x-d]$$
for every $1\le x\le10^6$, with no mismatch.

However, direct greedy simulation is still impossible: for $n=10^{18}$ the answer is about $1.1\cdot10^{17}$ moves. We need to batch all operations inside decimal blocks.

### Recursive block meaning / 递归块含义

Define `reduce_block(v, M)` as follows:

- `v` is a decimal suffix;
- $M$ is the largest digit outside this suffix (in the fixed higher prefix);
- repeatedly subtract the greedy digit $\max(M,\text{digits of }v)$ until the suffix becomes negative, i.e. causes one borrow from the higher prefix;
- return both the number of subtractions and the negative remainder after that borrow.

For a one-digit suffix $v<10$, only one subtraction is needed (unless both $v$ and $M$ are zero): subtract $\max(v,M)$ and return remainder $v-\max(v,M)$.

For a longer value, write
$$v=d\cdot p+r,$$
where $p$ is its highest power of ten, $d$ the leading digit, and $r<p$ the suffix. While the leading digit remains positive:

1. recursively reduce the suffix $r$ with outside maximum $\max(M,d)$;
2. add its step count;
3. combine its negative remainder back with $d\cdot p$.

The negative suffix remainder automatically performs exactly one borrow from the leading digit. Repeat until the leading digit vanishes. The remaining value is now below $p$, so recursively process it with the original outside maximum $M$.

Example $27$:

- suffix $7$ with outside maximum $2$ subtracts $7$: $27\to20$;
- suffix $0$ with outside maximum $2$ returns $-2$: $20\to18$;
- suffix $8$ with outside maximum $1$ subtracts $8$: $18\to10$;
- suffix $0$ with outside maximum $1$ returns $-1$: $10\to9$;
- process $9$: $9\to0$.

Total: five steps.

Memoize states by `(value, outside maximum)`. The outside maximum has only ten possibilities, and each recursive call removes or decreases a leading digit, so only a small number of decimal-boundary states are reached even for $10^{18}$.

对该操作而言，每步减去当前出现的最大数字是最优的。可以通过价值函数的单调性证明：更大的合法减法会到达一个不会更难的更小状态，而十进制借位结构不会让“先减较小数字”得到足以抵消差距的优势。作为直接验证，将贪心与精确递推
$$dp[x]=1+\min_{d\text{ 是 }x\text{ 的非零数字}}dp[x-d]$$
在所有 $1\le x\le10^6$ 上逐值比较，零失配。

但直接模拟贪心仍不可行：$n=10^{18}$ 时答案约为 $1.1\cdot10^{17}$ 步。必须批量跳过十进制块内的操作。

定义 `reduce_block(v,M)`：

- `v` 是某个十进制后缀；
- $M$ 是固定高位前缀中的最大数字；
- 反复减去贪心数字 $\max(M,\text{v的各位})$，直到后缀变成负数，即向高位产生一次借位；
- 返回减法次数和借位后的负余量。

若后缀只有一位 $v<10$，只需一次减法（除非 $v=M=0$）：减去 $\max(v,M)$，返回余量 $v-\max(v,M)$。

对更长的值，写成
$$v=d\cdot p+r，$$
其中 $p$ 是最高十次幂，$d$ 是最高位，$r<p$ 是后缀。当最高位仍为正时：

1. 以外部最大值 $\max(M,d)$ 递归处理后缀 $r$；
2. 累加其步数；
3. 把后缀的负余量与 $d\cdot p$ 重新组合。

负余量会自动让最高位恰好借位一次。重复直到最高位消失。此时剩余值小于 $p$，再用原外部最大值 $M$ 递归处理。

以 $27$ 为例，递归批量过程对应
$$27\to20\to18\to10\to9\to0，$$
共五步，与样例一致。

按 `(value, 外部最大位)` 记忆化。外部最大位只有10种可能，每次递归都会删除或降低某个最高位，因此即使输入为 $10^{18}$，实际访问的十进制边界状态也很少。

## Complexity / 复杂度

The number of memoized decimal-boundary states is polynomial in the digit count and tiny for at most 19 digits; each state performs at most ten leading-digit iterations. In practice this is effectively $O(\text{digits}^2)$ time and memory, independent of the enormous answer value.

记忆化的十进制边界状态数量是位数的多项式；最多19位时极小，每个状态最多循环10次最高位。实践中可视为 $O(\text{digits}^2)$ 时间与空间，与巨大答案值无关。
