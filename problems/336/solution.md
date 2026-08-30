# 336 - Grid Completion

## Problem / 题目

Complete an $n\times n$ grid (some cells already contain `A` or `B`, guaranteed at most one `A` and one `B` per row and per column) so that every row and every column ends up with exactly one `A` and one `B`. Count the number of ways, modulo $10^9+7$.

补全一个 $n\times n$ 网格（部分格子已有 `A` 或 `B`，保证每行每列最多已有一个 `A` 和一个 `B`），使得每行每列恰好有一个 `A` 和一个 `B`。求方案数，对 $10^9+7$ 取模。

## Idea / 思路

Placing all the `A`s is choosing a permutation $p$ (row $i$'s `A` goes to column $p(i)$); placing all the `B`s is choosing a permutation $q$. The only interaction between them is that **no cell can hold both**, i.e. $p(i)\ne q(i)$ for every row $i$. Split the rows into four kinds based on what's already given:

- **AB** rows: both fixed, and automatically $p(i)\ne q(i)$ (they're different cells already) — no work needed.
- **A-only** rows: $p(i)$ fixed to a known column $a_i$; $q(i)$ is free but must avoid $a_i$ — a forbidden position purely on $q$'s side.
- **B-only** rows: symmetric — $q(i)$ fixed to $b_i$; $p(i)$ must avoid $b_i$.
- **N** rows: both free, and $p(i)$ must simply differ from whatever $q(i)$ turns out to be — a genuine *mutual* constraint.

Let $u_p$ = rows without a placed `A` (= B-only + N rows) = number of free columns for $p$'s completion, and $u_q$ similarly for $q$. The forbidden positions coming from A-only/B-only rows form a **partial matching** (each forbidden column is used by only one such row, since a column has at most one `A`/`B`), so completing $p$ while avoiding the $j_p$ *still-available* forbidden columns (a forbidden column $b_i$ only matters if it isn't already occupied by someone else's `A`) is the classical "derangement with $j$ forbidden positions" count:
$$R(\text{pool},j,s)=\sum_{t=0}^{j}(-1)^t\binom{j}{t}(\text{pool}-s-t)!$$
(inclusion–exclusion: force $t$ of the $j$ forbidden pairs to happen, the rest is a free permutation of what remains; the extra parameter $s$ accounts for rows already used up by the next step).

**Handling N rows.** For $s$ of the $n_N$ "both free" rows we might *force* $p(i)=q(i)$ (as a step in inclusion–exclusion to later subtract these bad cases out). Forcing agreement on $s$ chosen N-rows means picking $s$ *distinct* columns that are simultaneously free for both $p$ and $q$ (i.e. from $C_p\cap C_q$, columns with neither a placed `A` nor a placed `B`, of size $c$) and assigning them to the $s$ rows — $\binom{c}{s}\cdot s! = (c)_s$ ways (falling factorial). Crucially, such a shared column can never coincide with an active A-only/B-only forbidden column (a forbidden column for $p$ always already has a `B` on it, so it's never in $C_p\cap C_q$), so after removing $s$ rows and $s$ shared columns, the *remaining* completions of $p$ and $q$ still face exactly the same $j_p,j_q$ forbidden positions, just on a smaller pool — giving $R(u_p,j_p,s)$ and $R(u_q,j_q,s)$ respectively. Summing over $s$ with inclusion–exclusion signs removes exactly the games where some N-row was bad:

$$\text{answer}=\sum_{s=0}^{\min(n_N,c)}(-1)^s\binom{n_N}{s}(c)_s\cdot R(u_p,j_p,s)\cdot R(u_q,j_q,s).$$

*Sanity check (sample):* the sample grid has $1$ AB row, $1$ A-only row, $1$ B-only row, $2$ N rows; working out $u_p=u_q=3$, $j_p=1$, $j_q=0$, $c=2$, the sum gives $s{=}0:24$, $s{=}1:-8$, $s{=}2:0$, total $16$ — exactly the sample answer.

放好所有 `A` 等价于选一个置换 $p$（第 $i$ 行的 `A` 落在第 $p(i)$ 列）；放好所有 `B` 等价于选一个置换 $q$。两者唯一的相互影响是**同一格不能同时是两者**，即每行 $p(i)\ne q(i)$。按已知信息把行分成四类：

- **AB 行**：$p(i),q(i)$ 都已固定，且天然不同（本来就是两个不同的格子）——无需处理。
- **仅 A 行**：$p(i)$ 固定为已知列 $a_i$；$q(i)$ 自由，但必须避开 $a_i$——这是 $q$ 单方面的禁止位置。
- **仅 B 行**：对称——$q(i)$ 固定为 $b_i$；$p(i)$ 必须避开 $b_i$。
- **N 行**：两者都自由，只需 $p(i)$ 不等于最终的 $q(i)$——这是真正的**相互**约束。

设 $u_p$ = 没有已放 `A` 的行数（= 仅 B 行 + N 行）= $p$ 补全时可用的自由列数，$u_q$ 类似。仅 A/仅 B 行带来的禁止位置构成一个**部分匹配**（每个禁止列只被一行占用，因为一列最多一个 `A`/`B`），所以完成 $p$ 时避开这 $j_p$ 个（仍然可用的）禁止列，就是经典的"带 $j$ 个禁止位置的错位排列数"：
$$R(\text{pool},j,s)=\sum_{t=0}^{j}(-1)^t\binom{j}{t}(\text{pool}-s-t)!$$
（容斥：强制 $t$ 个禁止对发生，剩下自由排列；额外参数 $s$ 用于扣除下一步已经用掉的行数）。

**处理 N 行。** 对 $n_N$ 个"两者都自由"的行中选出 $s$ 个，*强制* $p(i)=q(i)$（作为容斥的一步，之后再把这些坏情况减掉）。在选定的 $s$ 个 N 行上强制相等，意味着挑选 $s$ 个**同时**对 $p,q$ 都空闲的列（即没有已放 `A` 也没有已放 `B` 的列，共 $c$ 个，属于 $C_p\cap C_q$）分配给这 $s$ 行——共 $\binom{c}{s}\cdot s!=(c)_s$ 种（降阶乘）。关键是，这样的共享列永远不可能与仅 A/仅 B 行的有效禁止列重合（$p$ 的禁止列本身必然已经放了 `B`，所以绝不可能同时属于 $C_p\cap C_q$），于是去掉这 $s$ 行和 $s$ 个共享列之后，$p,q$ 剩余部分要面对的禁止位置个数仍然还是原来的 $j_p,j_q$，只是池子变小了——分别给出 $R(u_p,j_p,s)$ 与 $R(u_q,j_q,s)$。对 $s$ 求和并加上容斥符号，恰好把"某个 N 行出问题"的情形都减掉：

$$\text{答案}=\sum_{s=0}^{\min(n_N,c)}(-1)^s\binom{n_N}{s}(c)_s\cdot R(u_p,j_p,s)\cdot R(u_q,j_q,s)。$$

*验证（样例）：* 样例网格有 $1$ 个 AB 行、$1$ 个仅 A 行、$1$ 个仅 B 行、$2$ 个 N 行；算出 $u_p=u_q=3$，$j_p=1$，$j_q=0$，$c=2$，求和得 $s{=}0:24$，$s{=}1:-8$，$s{=}2:0$，总和 $16$——恰好是样例答案。

## Complexity / 复杂度

The outer sum over $s$ has $O(n)$ terms, each evaluating two $O(n)$ inclusion–exclusion sums $R(\cdot,\cdot,s)$, giving $O(n^2)$ overall. With $n\le500$ this is at most about $2.5\times10^5$ operations.

对 $s$ 的外层求和有 $O(n)$ 项，每项计算两次 $O(n)$ 的容斥和 $R(\cdot,\cdot,s)$，总体 $O(n^2)$。$n\le500$ 时至多约 $2.5\times10^5$ 次操作。
