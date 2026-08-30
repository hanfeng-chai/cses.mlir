# 196 - Another Game

## Problem / 题目
There are $n$ heaps of coins. A move selects any non-empty subset of the non-empty heaps and removes exactly one coin from each chosen heap; last to remove a coin wins. Decide the winner.

有 $n$ 堆硬币。每步选取若干（至少一个）非空堆，从每个被选堆各取走恰好一枚；取走最后一枚者胜。判断胜者。

## Idea / 思路
A position with all heaps even is a P-position (previous player wins): any move turns at least one heap odd, leaving an N-position. Conversely, if some heap is odd, the player to move can decrement exactly the odd heaps, reaching an all-even position. Hence the first player wins iff at least one heap is odd.

所有堆均为偶数的局面是 P-局面（上一手玩家胜）：任何一步都会把至少一堆变为奇数，留下 N-局面。反之，若存在奇数堆，行动方可恰好对所有奇数堆各取一枚，到达全偶局面。因此先手胜当且仅当至少有一堆为奇数。

## Complexity / 复杂度
$O(n)$ per test. 每组 $O(n)$。
