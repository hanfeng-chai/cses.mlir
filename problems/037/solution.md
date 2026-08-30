# 037 - Playlist

## Problem / 题目

Find the length of the longest contiguous run of songs in which every song id is unique.

求最长的连续歌曲段的长度，使其中每个歌曲编号都互不相同。

## Idea / 思路

Use a sliding window with two pointers. Keep the last seen position of each id; as the right end $r$ advances, if the current song last appeared at a position $\ge$ the window's left end $l$, move $l$ just past that occurrence. The window $[l, r]$ is always duplicate-free, and we track its maximum length.

使用双指针滑动窗口。记录每个编号最近出现的位置；右端 $r$ 前进时，若当前歌曲上次出现的位置 $\ge$ 窗口左端 $l$，就把 $l$ 移到那次出现之后。窗口 $[l, r]$ 始终无重复，我们记录它的最大长度。

## Complexity / 复杂度

Each pointer moves at most $n$ times, so the time is $O(n)$.

每个指针至多移动 $n$ 次，因此时间为 $O(n)$。
