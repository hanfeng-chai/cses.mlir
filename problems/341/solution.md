# 341 - Shortest Subsequence

## Problem / 题目

Given a DNA string (alphabet `A,C,G,T`) of length $n$, construct the shortest string over the same alphabet that is **not** a subsequence of it. Multiple valid answers of the minimum length are accepted.

给定一个字母表为 `A,C,G,T` 的长度为 $n$ 的 DNA 串，构造一个最短的、**不是**它的子序列的同字母表字符串。只要长度最短，任何合法答案都可以。

## Idea / 思路

Think of the classical "does string $T$ appear as a subsequence of $S$" check: a two-pointer scan where a pointer into $S$ advances greedily whenever it matches the current character of $T$. We are constructing $T$ character by character, and we *control* which character to append; we win (make $T$ fail to be a subsequence) as soon as the scan pointer in $S$ runs past the end without finding a needed character.

Precompute, for every position $i$ of $S$ (including the virtual position $n$, meaning "already past the end") and every letter $c$, `nxt[i][c]` = the first occurrence of $c$ at position $\ge i$, or $n$ (a sentinel) if $c$ does not occur again. This is built with one backward pass in $O(n)$.

Now define $f[i]$ = the length of the shortest suffix-of-our-construction that fails to be a subsequence of $S[i:]$ (the "remaining string to beat"), for $i=0,\dots,n$. For each candidate next character $c$:
- if `nxt[i][c] == n` (that letter never occurs again from $i$ onward), appending $c$ **immediately** wins — cost $1$.
- otherwise the scan pointer advances to `nxt[i][c]+1`, and we still need $f[\text{nxt}[i][c]+1]$ more characters — cost $1+f[\text{nxt}[i][c]+1]$.

We (the constructor) get to pick whichever of the 4 letters is cheapest, so $f[i]=\min_c(\dots)$. This is computed from $i=n$ down to $0$ (note $f[n]=1$ automatically, since with an empty remaining string every letter is instantly "not found"). The answer length is $f[0]$; the actual string is reconstructed by walking forward from position $0$, always taking the character that achieved the minimum, and jumping the pointer to `nxt[pos][c]+1` until a letter is found to be entirely missing.

Because several different shortest strings can exist (e.g. any letter that's globally rarest at some intermediate step may tie with another), this problem is graded by a custom checker that only checks the length matches the optimum and that the string genuinely fails the subsequence test — not exact string equality.

考虑经典的"字符串 $T$ 是否是 $S$ 的子序列"判定：用双指针扫描，$S$ 上的指针每次匹配到 $T$ 当前字符就前移。我们在一个个构造 $T$，并且**可以自己选**接下来放哪个字符；一旦 $S$ 上的指针跑出末尾还没找到需要的字符，我们就赢了（$T$ 不是子序列）。

预处理：对 $S$ 的每个位置 $i$（包括虚拟位置 $n$，表示"已经越过末尾"）与每个字母 $c$，求 `nxt[i][c]` = 位置 $\ge i$ 处 $c$ 的第一次出现，若再也不出现则记为哨兵值 $n$。这只需要一次反向扫描，$O(n)$。

定义 $f[i]$ = 从"剩余串" $S[i:]$ 开始、构造一个使其失败（非子序列）所需的最短长度，$i=0,\dots,n$。对每个候选下一个字符 $c$：
- 若 `nxt[i][c] == n`（该字母从 $i$ 往后再也不出现），追加 $c$**立即**获胜——代价 $1$。
- 否则扫描指针前进到 `nxt[i][c]+1`，还需要 $f[\text{nxt}[i][c]+1]$ 个字符——代价 $1+f[\text{nxt}[i][c]+1]$。

我们（构造者）可以挑 4 个字母里最便宜的那个，所以 $f[i]=\min_c(\dots)$。从 $i=n$ 递推到 $0$（注意 $f[n]=1$ 自动成立，因为剩余串为空时任何字母都"立即找不到"）。答案长度是 $f[0]$；实际字符串通过从位置 $0$ 往前走、每次取达到最小值的那个字符、并跳到 `nxt[pos][c]+1`，直到某个字母彻底找不到为止来重建。

由于可能存在多个不同的最短字符串（例如某一步里并列"最稀有"的字母不止一个），本题用自定义 checker 评测，只检查长度是否等于最优值、以及字符串确实不是子序列——而不是逐字符比较。

## Complexity / 复杂度

$O(4n)$ time and memory for the DP table and the `nxt` table.

DP 表与 `nxt` 表均为 $O(4n)$ 时间和空间。
