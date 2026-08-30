# 347 - Bubble Sort Rounds I

## Problem / 题目

Bubble sort repeatedly scans the array left to right, swapping adjacent out-of-order elements, until it is fully sorted. Given an array (possibly with equal values), find the number of rounds (full left-to-right scans) needed.

冒泡排序反复从左到右扫描数组，交换相邻的逆序对，直到数组有序为止。给定一个数组（可能有相同的值），求需要的轮数（完整的从左到右扫描次数）。

## Idea / 思路

A single left-to-right bubble pass is exactly: keep a running "carry" equal to the maximum of everything scanned so far; whenever the carry beats the next element, they swap (the carry keeps moving right — possibly through *many* elements in the same pass!), otherwise the next element itself becomes the new carry.

The key fact this reveals: a specific element **only ever moves left**, and moves left by *exactly* one position in a round, **exactly when** there is currently at least one bigger element somewhere to its left (that bigger element, or an even bigger one further left, is guaranteed to be the carry reaching it and beating it). If nothing to its left is bigger, it does not move left at all that round (it may move right instead, which is irrelevant to when it "settles").

So define, for each element at original position $i$, $L_i=\#\{j<i : x_j>x_i\}$ — the count of elements originally to its left that must eventually end up to its right. This quantity decreases by exactly $1$ every round (while positive), so element $i$ needs *exactly* $L_i$ rounds before nothing bigger remains to its left — and the whole array is sorted exactly when **every** element has reached this state, i.e. after $\max_i L_i$ rounds.

(Note this is a plain *count*, not a "longest strictly-decreasing chain" — with many equal or near-equal values, several originally-left elements can all be swept past an element in the very same round, so a chain-based recurrence undercounts; the plain count is the one that matches the actual round-by-round mechanics.)

$L_i$ for all $i$ is computed with one left-to-right pass using a Fenwick tree over coordinate-compressed values: before inserting $x_i$, query how many of the already-inserted (i.e. $j<i$) values are $>x_i$.

一次从左到右的冒泡扫描，本质上就是：维护一个"携带值"，等于目前扫描过的所有元素的最大值；每当携带值比下一个元素大，就交换（携带值继续往右走——在同一轮里可能连续越过*好几个*元素！），否则下一个元素本身成为新的携带值。

由此可见一个关键事实：某个元素**只会往左移动**，并且*恰好*在"目前它左边还存在至少一个比它大的元素"时，在这一轮里向左移动恰好一步（那个更大的元素，或者它左边更靠前的某个更大元素，一定会作为携带值到达并压过它）。如果它左边已经没有比它大的了，这一轮它完全不会向左移动（可能会向右移动，但这与它"何时稳定"无关）。

于是对原始位置 $i$ 上的元素，定义 $L_i=\#\{j<i : x_j>x_i\}$——它左边原本存在、终将要移到它右边去的元素个数。这个量每一轮恰好减少 $1$（只要它还大于 $0$），所以元素 $i$ 恰好需要 $L_i$ 轮才能让左边不再有比它大的——而整个数组排好序，正是**所有**元素都达到这个状态的时刻，即第 $\max_i L_i$ 轮。

（注意这是单纯的*计数*，不是"最长严格下降链"——当有很多相同或相近的值时，同一轮里可能有好几个原本在左边的元素被同时扫过某个元素，链式递推会算少；单纯计数才符合实际逐轮机制。）

用一次从左到右扫描配合按值离散化的树状数组，就能算出所有 $L_i$：插入 $x_i$ 之前，先查询已插入（即 $j<i$）的值里有多少个 $>x_i$。

## Complexity / 复杂度

$O(n\log n)$ time (Fenwick tree operations with coordinate compression), $O(n)$ memory.

时间 $O(n\log n)$（离散化后的树状数组操作），空间 $O(n)$。
