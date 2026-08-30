# 076 - Mountain Range

## Problem / 题目

There are $n$ mountains in a row with given heights. You may glide from mountain $a$ to mountain $b$ if $a$ is **strictly taller** than $b$ and taller than every mountain between them. Starting from any mountain, what is the maximum number of mountains you can visit?

一排 $n$ 座山，高度已知。当 $a$ **严格高于** $b$ 且高于它们之间的所有山时，可以从山 $a$ 滑翔到山 $b$。从任意一座山出发，最多能经过多少座山？

## Idea / 思路

Let $f[i]$ be the longest route starting at mountain $i$. From $i$ you can glide to any mountain inside its **visible window** — the open interval bounded on each side by the nearest mountain of height $\ge h[i]$ (an equal-or-taller mountain blocks the view). Every mountain in that window is strictly lower, so $f[i] = 1 + \max f[j]$ over the window. We process mountains in increasing height (so every reachable, strictly lower mountain is already known) and use a segment tree for the range-maximum of $f$ over each window. Equal-height mountains never lie strictly inside one another's window, so they are naturally not connected. A tempting "height of the max Cartesian tree" approach is **wrong** here: when several equal-height sub-peaks share a window, it fails to let a taller mountain reach all of them.

设 $f[i]$ 为从山 $i$ 出发的最长路线。从 $i$ 可以滑到它**可视窗口**内的任意山——该窗口是两侧各被最近的高度 $\ge h[i]$ 的山界定的开区间（等高或更高的山会挡住视线）。窗口内的山都严格更矮，故 $f[i] = 1 + \max f[j]$（$j$ 取遍窗口）。我们按高度升序处理（这样每个可达的、严格更矮的山都已算好），并用线段树求每个窗口内 $f$ 的区间最大值。等高的山永远不会严格落在彼此窗口内，因此自然不会相连。这里"求最大值笛卡尔树的高度"这种看似可行的做法是**错的**：当多个等高次峰共享一个窗口时，它无法让更高的山到达所有这些次峰。

## Complexity / 复杂度

Sorting by height plus $n$ segment-tree operations gives $O(n \log n)$.

按高度排序加上 $n$ 次线段树操作，为 $O(n \log n)$。
