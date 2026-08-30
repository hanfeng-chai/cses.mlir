# 215 - Substring Order I

## Problem / 题目
Among all *distinct* substrings ordered lexicographically, output the $k$-th smallest ($n\le 10^5$).

在所有**不同**子串按字典序排列中，输出第 $k$ 小者（$n\le 10^5$）。

## Idea / 思路
Build the suffix automaton. For each state compute $f[v]$, the number of distinct substrings reachable from $v$ (itself excluded), via $f[v]=\sum_c\big(1+f[\text{to}(v,c)]\big)$ in order of decreasing length. Then descend greedily from the initial state: for letters `a..z`, a branch into child $u$ accounts for $1+f[u]$ substrings; subtract whole blocks until the right branch is found, append the letter, and stop when $k$ reaches $0$.

构造后缀自动机。对每个状态按长度递减计算 $f[v]$——从 $v$ 出发可达的不同子串数（不含 $v$ 自身）：$f[v]=\sum_c\big(1+f[\text{to}(v,c)]\big)$。再从初始状态贪心下行：对字母 `a..z`，走向子结点 $u$ 的分支含 $1+f[u]$ 个子串；逐块减去直到定位分支，追加字母，$k$ 减到 $0$ 时停止。

## Complexity / 复杂度
$O(n)$ build plus $O(|\text{answer}|\cdot\Sigma)$ descent. 建造 $O(n)$，下行 $O(|\text{答案}|\cdot\Sigma)$。
