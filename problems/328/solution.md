# 328 - Border Subgrid Count II

## Problem / 题目

For each of the first $k$ letters, count rectangular subgrids whose entire border consists of that letter. Rectangles of width or height one are also valid when all cells on that line have the same letter.

对前 $k$ 个字母分别统计：边框全部由该字母组成的矩形子网格数量。宽或高为1的矩形也属于合法矩形，只要该线段上的格子全为同一字母。

## Idea / 思路

Enumerate the top and bottom rows $t,b$. Let the rectangle height be $h=b-t+1$. Scan columns from left to right.

For a column $x$ to lie inside the horizontal-border span of a letter-$c$ rectangle, both `grid[t][x]` and `grid[b][x]` must be $c$. Thus columns are divided into maximal consecutive runs where the top and bottom cells are equal to the same letter. Any rectangle's left and right boundaries must belong to the same run; crossing a mismatching column would break the top or bottom border.

Within one such run, a column can serve as a vertical boundary exactly when all cells from row $t$ through $b$ in that column equal $c$. Precompute
$$up[b][x]=\text{the same-letter run length ending at $(b,x)$ and going upward}.$$
Then column $x$ is a legal vertical boundary iff `up[b][x] >= h`.

While scanning one run, let `count` be the number of earlier columns that are legal vertical boundaries. When the current column is also legal, it can pair with each of those `count` columns to form a positive-width rectangle, and it can pair with itself to form a width-one rectangle. Therefore add
$$count+1$$
to the answer for $c$, then increment `count`. A column whose vertical side is invalid does **not** reset `count`: it may still be an interior column, because its top and bottom cells are $c$. Only a change/mismatch in the top-bottom letter resets the run.

When $t=b$, every column has vertical length at least one, so the same logic counts every same-letter horizontal segment. Thus height-one rectangles need no special case.

枚举矩形的上边界行 $t$ 和下边界行 $b$，高度为 $h=b-t+1$，然后从左到右扫描列。

若某列 $x$ 位于字母 $c$ 矩形的上下边框跨度内，则 `grid[t][x]` 与 `grid[b][x]` 都必须为 $c$。因此列会被划分为若干最大连续段，每段中上下两个格子都等于同一字母。一个矩形的左右边界必须在同一段中；跨过上下字母不匹配的列会破坏上边或下边。

在一个连续段内，某列能作为竖直边界，当且仅当第 $t$ 到 $b$ 行的所有格子都为 $c$。预处理
$$up[b][x]=\text{从 $(b,x)$ 向上结束的同字母连续长度}。$$
于是 `up[b][x] >= h` 恰好表示该列是合法竖边。

扫描当前连续段时，令 `count` 为此前合法竖边列数。若当前列也合法，它可以与此前每个合法列组成一个宽度大于1的矩形，还可以与自身组成宽度1的矩形，因此给字母 $c$ 的答案增加
$$count+1，$$
再令 `count++`。若当前列竖边不完整，**不能**重置 `count`：它仍可作为矩形内部列，因为它的上下两个格子都是 $c$。只有上下字母发生变化或不相等时，才结束当前连续段并清零。

当 $t=b$ 时，每列的竖直长度都至少为1，同一逻辑会统计每个同字母水平线段，因此无需特判高度1的矩形。

## Complexity / 复杂度

There are $O(n^2)$ row pairs and each scans $n$ columns, so time is $O(n^3)$. The upward-run table uses $O(n^2)$ memory.

共有 $O(n^2)$ 组上下边界，每组扫描 $n$ 列，时间复杂度为 $O(n^3)$。向上连续长度表占 $O(n^2)$ 空间。
