# 364 - Bit Inversions

## Problem / 题目

Given a bit string, after each of $m$ single-bit flips, report the length of the longest substring consisting of a single repeated bit (all `0`s or all `1`s).

给定一个位字符串，每次翻转一个位之后，输出最长的"由同一个位重复组成"的子串长度（全 `0` 或全 `1`）。

## Idea / 思路

This is the standard **"longest run of equal characters" segment tree**. Each node covering a range stores six numbers: the range length; the longest all-`0` / all-`1` **prefix** run; the longest all-`0` / all-`1` **suffix** run; and `best`, the longest same-bit run anywhere inside the range.

Merging two children `L` (left) and `R` (right):
- `pref0` = if `L` is *entirely* `0`s, extend across into `R`'s leading `0`s (`L.len + R.pref0`); otherwise just `L.pref0`. (`pref1` symmetric.)
- `suf0` = if `R` is *entirely* `0`s, extend across into `L`'s trailing `0`s (`R.len + L.suf0`); otherwise just `R.suf0`. (`suf1` symmetric.)
- `best` = the best of `L.best`, `R.best`, and the run straddling the boundary: `L.suf0+R.pref0` or `L.suf1+R.pref1`.

A leaf just encodes a single bit. Flipping bit $x$ is a point update: recompute the leaf, then recompute all $O(\log n)$ ancestors bottom-up via the same merge — giving the new global `best` (stored at the root) in $O(\log n)$.

这是标准的**"最长同字符连续段"线段树**。每个覆盖一段区间的节点存六个数：区间长度；最长的全 `0` / 全 `1` **前缀**段；最长的全 `0` / 全 `1` **后缀**段；以及 `best`——区间内最长的同位连续段。

合并左右子节点 `L`、`R`：
- `pref0` = 若 `L` *整段*都是 `0`，就延伸到 `R` 开头的 `0`（`L.len + R.pref0`）；否则就是 `L.pref0`（`pref1` 对称）。
- `suf0` = 若 `R` *整段*都是 `0`，就延伸到 `L` 末尾的 `0`（`R.len + L.suf0`）；否则就是 `R.suf0`（`suf1` 对称）。
- `best` = `L.best`、`R.best`，以及跨越分界处的段（`L.suf0+R.pref0` 或 `L.suf1+R.pref1`）三者中的最大值。

叶子节点就编码单个位。翻转第 $x$ 位是一次单点更新：重新计算该叶子，再沿路径自底向上重新计算 $O(\log n)$ 个祖先节点（用同样的合并规则），根节点存的 `best` 就是新的全局答案，单次操作 $O(\log n)$。

## Complexity / 复杂度

$O(n)$ to build, $O(\log n)$ per update. Overall $O(n+m\log n)$.

建树 $O(n)$，每次更新 $O(\log n)$。总体 $O(n+m\log n)$。
