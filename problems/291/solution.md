# 291 - Chess Tournament

## Problem / 题目
Each of $n$ players wants to play a given number of games; each pair plays at most once. Output a set of games realizing the wishes, or IMPOSSIBLE.

$n$ 名选手各想下指定数量的棋；每对至多下一局。输出实现愿望的对局集合，或 IMPOSSIBLE。

## Idea / 思路
This is graph realization of a degree sequence. Use the Havel–Hakimi procedure with a max-heap: repeatedly take the player with the largest remaining demand $d$ and connect them to the $d$ next-highest players, decrementing each. If at some point fewer than $d$ players are available, the sequence is not realizable. The total degree must also be even.

这是度序列的图实现。用最大堆做 Havel–Hakimi：反复取剩余需求最大的选手 $d$，与接下来 $d$ 个需求最高的选手连边并各自减一。若某刻可用选手不足 $d$，则不可实现。总度数还须为偶。

## Multi-solution / 多解
Any valid game set is accepted; a custom checker verifies each player's count and the absence of duplicate or self games.

任意合法对局集均可；checker 验证每名选手对局数、无重复与自环。

## Complexity / 复杂度
$O(\sum x_i\log n)$. $O(\sum x_i\log n)$。
