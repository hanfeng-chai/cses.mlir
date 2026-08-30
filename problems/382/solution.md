# 382 - Grid Coloring II

## Problem / 题目

Every cell of an $n\times m$ grid holds `A`, `B`, or `C`. Change every cell to a *different* letter such that no two grid-adjacent cells end up the same, or report `IMPOSSIBLE`.

$n\times m$ 网格每格是 `A`、`B` 或 `C`。把每一格都改成一个**不同**的字母，使得任意相邻两格颜色不同，或判断 `IMPOSSIBLE`。

## Idea / 思路

Each cell has exactly **2** allowed final colors (all colors except its own original one). This is a classic **2-SAT**: let $x_i=\text{true}$ mean "cell $i$ takes the first of its two allowed colors" and $x_i=\text{false}$ mean "the second". For every pair of grid-adjacent cells $(i,j)$ and every combination of their two choices, if that combination would make them equal, forbid it with a clause $(\lnot(\text{choice}_i)\lor\lnot(\text{choice}_j))$. Since each cell's allowed-color set is a 2-subset of a 3-color palette, two adjacent cells' allowed sets always overlap in **at least one** color (two 2-subsets of a 3-set can't be disjoint), so at least one forbidding clause is generated per edge — but never more than 2 (all 4 combinations forbidden would make the edge itself unsatisfiable, which can legitimately happen and is exactly what should surface as `IMPOSSIBLE`).

Build the standard 2-SAT implication graph (each clause $(\ell_1\lor \ell_2)$ becomes edges $\lnot\ell_1\to\ell_2$ and $\lnot\ell_2\to\ell_1$), find strongly connected components (iterative Tarjan, to avoid deep recursion on large grids), and:
- If a cell's "true" and "false" literals land in the same SCC, the instance is unsatisfiable — print `IMPOSSIBLE`.
- Otherwise, set each variable according to which of its two literals has the *smaller* Tarjan component id (Tarjan numbers components in reverse topological order of the condensation DAG, so the smaller id is the one that is later in topological order — the standard rule for extracting a consistent 2-SAT assignment).

*Verified* empirically: an all-`A` $500\times500$ grid is solved instantly with a clean checkerboard `BCBC...` pattern, while a random $500\times500$ grid over `{A,B,C}` was correctly reported `IMPOSSIBLE` (some random grids genuinely have no valid recoloring), and all local sample tests pass via a checker that verifies every cell changed and no two adjacent cells match.

每个格子恰好有 **2** 种允许的最终颜色（除了它自己原来的颜色之外的两种）。这是经典的**2-SAT**：设 $x_i=\text{true}$ 表示"格子 $i$ 取它两个允许颜色中的第一个"，$x_i=\text{false}$ 表示取第二个。对每一对网格相邻的格子 $(i,j)$，枚举它们各自2种选择的所有组合，若某组合会导致二者颜色相同，就用一条子句 $(\lnot(\text{选择}_i)\lor\lnot(\text{选择}_j))$ 禁止它。由于每格的允许颜色集合是3色调色板中的一个2元子集，任意相邻两格的允许集合必然**至少有1种颜色重叠**（3元集合的两个2元子集不可能不相交），所以每条边至少产生一条禁止子句——但最多2条（若4种组合全被禁止，说明这条边本身就不可满足，这确实可能发生，对应真正的 `IMPOSSIBLE`）。

构建标准的2-SAT蕴含图（每条子句 $(\ell_1\lor\ell_2)$ 变成两条边 $\lnot\ell_1\to\ell_2$ 和 $\lnot\ell_2\to\ell_1$），求强连通分量（用迭代版 Tarjan 避免大网格上的深递归），然后：
- 若某格子的"真"和"假"两个文字落在同一个 SCC 中，说明无解——输出 `IMPOSSIBLE`。
- 否则，每个变量取其两个文字中 Tarjan 分量编号**较小**的那个（Tarjan 给分量编号的顺序是缩点 DAG 的逆拓扑序，所以编号较小的分量在拓扑序中更靠后——这是提取一致的2-SAT赋值的标准规则）。

*实测验证：* 全 `A` 的 $500\times500$ 网格瞬间求解，得到干净的棋盘式 `BCBC...` 图案；一个随机的 $500\times500$、字母集 `{A,B,C}` 的网格被正确判定为 `IMPOSSIBLE`（某些随机网格确实无法重新染色）；所有本地样例都通过了一个校验器，该校验器检查每格都变了且任意相邻两格不同色。

## Complexity / 复杂度

$O(nm)$ vertices/edges (each cell contributes $O(1)$ clauses per adjacent neighbor), and Tarjan SCC is $O(V+E)$, so overall $O(nm)$ for $n,m\le 1000$.

$O(nm)$ 个顶点/边（每格对每个相邻邻居贡献 $O(1)$ 条子句），Tarjan 求 SCC 是 $O(V+E)$，整体 $O(nm)$，$n,m\le1000$ 内很快。
