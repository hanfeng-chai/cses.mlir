# 273 - Permuted Binary Strings

## Problem / 题目
Recover a hidden permutation of $1..n$ ($n\le 1000$): a query sends a binary string $b$ and receives $b_{a_1}b_{a_2}\dots b_{a_n}$. At most $10$ queries.

还原 $1..n$（$n\le 1000$）的隐藏排列：一次询问发送二进制串 $b$，收到 $b_{a_1}b_{a_2}\dots b_{a_n}$。至多 $10$ 次。

## Idea / 思路
Encode each index in binary. In query $t$ set $b_j$ to bit $t$ of $j$. The returned string's $i$-th character is then bit $t$ of $a_i$. Running over all $\lceil\log_2 n\rceil\le 10$ bit positions reveals the binary representation of every $a_i$.

把每个下标用二进制编码。第 $t$ 次询问令 $b_j$ 为 $j$ 的第 $t$ 位。则返回串第 $i$ 个字符即 $a_i$ 的第 $t$ 位。遍历全部 $\lceil\log_2 n\rceil\le 10$ 个位，即得每个 $a_i$ 的二进制表示。

## Complexity / 复杂度
$\lceil\log_2 n\rceil$ queries. $\lceil\log_2 n\rceil$ 次询问。
