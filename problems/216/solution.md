# 216 - Substring Order II

## Problem / 题目
Among all substrings (counted with multiplicity) ordered lexicographically, output the $k$-th smallest ($n\le 10^5$).

在所有子串（按出现次数计重）按字典序排列中，输出第 $k$ 小者（$n\le 10^5$）。

## Idea / 思路
Build the suffix automaton and compute each state's endpos size $\text{occ}$ (its number of occurrences). For each state compute $f[v]=\sum_c\big(\text{occ}(u)+f[u]\big)$ over children $u=\text{to}(v,c)$, the total occurrence-weighted count of substrings under $v$. Descend greedily: a branch into $u$ accounts for $\text{occ}(u)+f[u]$; once chosen, the substring ending at $u$ itself contributes $\text{occ}(u)$ copies, so stop if $k\le\text{occ}(u)$, otherwise subtract and continue deeper.

构造后缀自动机并计算每个状态的 endpos 大小 $\text{occ}$（出现次数）。对每个状态计算 $f[v]=\sum_c\big(\text{occ}(u)+f[u]\big)$（$u=\text{to}(v,c)$），即 $v$ 下方按出现次数计重的子串总数。贪心下行：走向 $u$ 的分支含 $\text{occ}(u)+f[u]$ 个；选定后，止于 $u$ 的子串本身贡献 $\text{occ}(u)$ 份，故 $k\le\text{occ}(u)$ 时停止，否则减去后继续深入。

## Complexity / 复杂度
$O(n)$ build plus $O(|\text{answer}|\cdot\Sigma)$ descent. 建造 $O(n)$，下行 $O(|\text{答案}|\cdot\Sigma)$。
