# 018 - Raab Game I

## Problem / 题目

Two players each hold cards $1, 2, \dots, n$. Every round both reveal one card; the player with the higher card scores a point (equal cards score nothing). Given $n$ and the final scores $a$ (player 1's points) and $b$ (player 2's points), construct any game that produces these scores, or report that none exists.

两名玩家各持有卡牌 $1, 2, \dots, n$。每回合双方各出一张；牌大的一方得一分（相等则不得分）。给定 $n$ 与最终比分 $a$（玩家 1 的分）和 $b$（玩家 2 的分），构造任意一种能产生该比分的对局，或报告不存在。

## Idea / 思路

A game exists **iff** $a + b \le n$ and $a, b$ are either both zero or both positive. The latter holds because both hands sum to the same value $1 + \dots + n$, so any round player 1 wins must be balanced by a round it loses; hence one score is zero only when the other is too. To build a game, let player 2 simply play $1, 2, \dots, n$ in order. For the first $a$ positions give player 1 the card $i + b$ (a win), for the next $b$ positions the card $i - a$ (a loss), and for the rest the card $i$ (a draw); these cards form exactly the permutation $1 \dots n$. Any valid game is accepted, so a problem-specific checker (`checker.cpp`) validates the two permutations and the resulting scores.

对局存在**当且仅当** $a + b \le n$ 且 $a, b$ 要么同为零、要么同为正。后者成立是因为两手牌的总和都等于 $1 + \dots + n$，所以玩家 1 赢的每一回合都必须由它输的一回合来平衡；因此一方得分为零时另一方也必为零。构造时让玩家 2 直接按顺序出 $1, 2, \dots, n$。前 $a$ 个位置给玩家 1 牌 $i + b$（赢），接下来 $b$ 个位置给牌 $i - a$（输），其余位置给牌 $i$（平）；这些牌恰好构成排列 $1 \dots n$。任意合法对局都被接受，故用题目专用 checker（`checker.cpp`）校验两个排列与得到的比分。

## Complexity / 复杂度

Each test builds the two length-$n$ sequences once, so the time is $O(n)$ per test.

每组数据只构造两个长度为 $n$ 的序列，因此每组是 $O(n)$。
