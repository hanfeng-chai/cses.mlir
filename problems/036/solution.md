# 036 - Collecting Numbers II

## Problem / 题目

Same setting as Collecting Numbers, but $m$ swap operations modify the array; report the number of rounds after each swap.

与 Collecting Numbers 相同，但有 $m$ 次交换操作修改数组；每次交换后报告所需轮数。

## Idea / 思路

The number of rounds equals $1$ plus the count of breakpoints (values $v$ with $pos[v] < pos[v-1]$). A breakpoint at $v$ depends only on $pos[v]$ and $pos[v-1]$. Swapping the positions of values $v_a$ and $v_b$ changes only $pos[v_a]$ and $pos[v_b]$, which can affect only the breakpoints at $\{v_a, v_a{+}1, v_b, v_b{+}1\}$. So we subtract those few old contributions, perform the swap, and add the new ones — constant work per query.

轮数等于 $1$ 加断点数（满足 $pos[v] < pos[v-1]$ 的值 $v$）。$v$ 处的断点只取决于 $pos[v]$ 与 $pos[v-1]$。交换值 $v_a$ 与 $v_b$ 的位置只改变 $pos[v_a]$、$pos[v_b]$，因而只可能影响 $\{v_a, v_a{+}1, v_b, v_b{+}1\}$ 处的断点。于是减去这几个旧贡献、执行交换、再加上新贡献——每次查询常数工作量。

## Complexity / 复杂度

Initial scan plus constant work per query gives $O(n + m)$.

初始扫描加每次查询常数工作量，为 $O(n + m)$。
