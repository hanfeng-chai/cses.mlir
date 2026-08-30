# 379 - Binary Subsequences

## Problem / 题目

Construct a shortest binary string having exactly $n$ distinct nonempty subsequences. Any shortest valid string is accepted.

构造一个最短二进制串，使其恰好有 $n$ 个不同的非空子序列。可以输出任意一个最短合法串。

## Idea / 思路

Let $e_0$ and $e_1$ be the numbers of distinct nonempty subsequences ending in `0` and `1`. Define
$$x=e_0+1,\qquad y=e_1+1.$$
Initially the string is empty, so $(x,y)=(1,1)$.

When appending `0`, every existing subsequence can be extended by `0`, and the one-character subsequence `0` is also created. The new set of subsequences ending in `0` has size $e_0+e_1+1$, while those ending in `1` do not change. Therefore
$$(x,y)\xrightarrow{0}(x+y,y).$$
Similarly,
$$(x,y)\xrightarrow{1}(x,x+y).$$
The total number of distinct nonempty subsequences is
$$e_0+e_1=x+y-2.$$
Thus we need to reach some positive pair $(x,y)$ satisfying
$$x+y=n+2.$$

Starting from $(1,1)$ and repeatedly adding one coordinate to the other always produces coprime coordinates. Conversely, every coprime positive pair can be reduced uniquely toward $(1,1)$ by subtracting the smaller coordinate from the larger; this is the subtractive Euclidean algorithm. Each subtraction identifies the final bit:

- if $x>y$, the last bit was `0`, and reverse it with $x\leftarrow x-y$;
- if $y>x$, the last bit was `1`, and reverse it with $y\leftarrow y-x$.

So every coprime split $x+(n+2-x)$ corresponds to a binary string, and its length equals the number of subtractive Euclidean steps. To find the shortest string, enumerate $1\le x\le(n+2)/2$ with $\gcd(x,n+2)=1$ and minimize this step count. Only half the splits are needed because swapping $x,y$ merely complements all bits and preserves length.

The subtraction count is computed in batches using Euclidean quotients. If $x>y>1$, then `x/y` consecutive final zeros can be removed at once by $x\mathrel{\%=}y$; if $y=1$, use only $x-1$ subtractions so the coordinate stops at $1$, not $0$. Record the corresponding repeated bits while reducing the best pair, then reverse the recorded string to obtain the forward construction.

For the sample $n=6$, the target sum is $8$. The best split is $(3,5)$:
$$(3,5)\xrightarrow{\text{remove }1}(3,2)\xrightarrow{\text{remove }0}(1,2)\xrightarrow{\text{remove }1}(1,1).$$
Reversing the removed bits gives `101`, whose six distinct nonempty subsequences match the sample.

令 $e_0,e_1$ 分别为以 `0`、`1` 结尾的不同非空子序列数量，定义
$$x=e_0+1,\qquad y=e_1+1。$$
空串初始时 $(x,y)=(1,1)$。

追加 `0` 时，每个已有子序列都可追加一个 `0`，并新产生单字符子序列 `0`。新的以0结尾子序列数量为 $e_0+e_1+1$，以1结尾的集合不变，因此
$$(x,y)\xrightarrow{0}(x+y,y)。$$
同理
$$(x,y)\xrightarrow{1}(x,x+y)。$$
不同非空子序列总数为
$$e_0+e_1=x+y-2。$$
所以目标是到达某个正整数对 $(x,y)$，满足
$$x+y=n+2。$$

从 $(1,1)$ 出发反复把一个坐标加到另一个坐标，得到的两个坐标始终互质。反过来，每个互质正整数对都可通过“较大者减较小者”的减法欧几里得算法唯一还原到 $(1,1)$。每次减法同时确定最后一个比特：

- 若 $x>y$，最后一位是 `0`，反向操作为 $x\leftarrow x-y$；
- 若 $y>x$，最后一位是 `1`，反向操作为 $y\leftarrow y-x$。

因此每个互质拆分 $x+(n+2-x)$ 都对应一个二进制串，其长度等于减法欧几里得步数。为求最短串，枚举 $1\le x\le(n+2)/2$ 且 $\gcd(x,n+2)=1$ 的拆分，取步数最少者。只枚举一半，因为交换 $x,y$ 只会把所有比特取反，不改变长度。

减法次数可用欧几里得商批量计算。若 $x>y>1$，可以一次删除 `x/y` 个连续末尾0，并令 $x\mathrel{\%=}y$；若 $y=1$，只能做 $x-1$ 次，使坐标停在1而非0。对最优整数对记录这些重复比特，最后反转记录串即得到正向构造。

样例 $n=6$ 时目标和为8，最优拆分是 $(3,5)$。反向欧几里得过程依次删除 `1,0,1`，反转后仍为 `101`，恰有6个不同非空子序列。

## Complexity / 复杂度

There are $O(n)$ candidate splits; each gcd and Euclidean length computation takes $O(\log n)$, so time is $O(n\log n)$ and memory is $O(\log n)$ for the output string.

候选拆分有 $O(n)$ 个，每次 gcd 与欧几里得长度计算为 $O(\log n)$，总时间 $O(n\log n)$，输出串占 $O(\log n)$ 空间。
