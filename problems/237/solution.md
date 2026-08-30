# 237 - Corner Subgrid Count

## Problem / 题目
Count the subgrids (height and width $\ge 2$) whose four corners are all black.

统计四角全为黑色的子网格（高、宽 $\ge 2$）个数。

## Idea / 思路
Store each row as a bitset of black columns. For every pair of rows, the columns that are black in both are given by the bitwise AND; if $c$ such columns exist they form $\binom{c}{2}$ subgrids. Summing over all row pairs gives the answer; the bitset AND and popcount make each pair fast.

把每行存为黑列的位集。对每对行，两行都黑的列由按位与给出；若有 $c$ 个这样的列则贡献 $\binom{c}{2}$ 个子网格。对所有行对求和即答案；位集与运算和 popcount 使每对很快。

## Complexity / 复杂度
$O(n^2\cdot n/64)$. $O(n^2\cdot n/64)$。
