# 175 - Permutation Rounds

## Problem / 题目
A permutation $p$ maps each position $i$ to $p_i$. Applying it repeatedly returns to the identity after some number of rounds; output that number modulo $10^9+7$.

排列 $p$ 把位置 $i$ 映到 $p_i$。反复作用若干轮后回到恒等映射，输出该轮数模 $10^9+7$。

## Idea / 思路
The number of rounds is the least common multiple of all cycle lengths. Decompose the permutation into cycles, factorize each cycle length, and keep the maximum exponent seen for every prime; the answer is the product of $p^{\text{maxexp}}$ modulo $10^9+7$.

轮数等于所有环长的最小公倍数。把排列分解成若干环，对每个环长做质因数分解，记录每个质数出现的最大指数；答案为 $\prod p^{\text{maxexp}}$ 模 $10^9+7$。

## Complexity / 复杂度
$O(n\sqrt{n})$ worst case for factorizing cycle lengths. 分解环长最坏 $O(n\sqrt{n})$。
