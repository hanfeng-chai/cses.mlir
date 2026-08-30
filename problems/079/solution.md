# 079 - Elevator Rides

## Problem / 题目

There are $n \le 20$ people with given weights and an elevator with a maximum load $x$. Find the minimum number of rides needed to carry everyone up.

有 $n \le 20$ 个人（重量已知）和一部最大载重 $x$ 的电梯。求把所有人送上去所需的最少乘坐次数。

## Idea / 思路

Do a bitmask DP over subsets of people. For each subset `mask` store a pair $dp[\text{mask}] = (\text{rides}, \text{weight of the last ride})$, taken as small as possible (compare rides first, then last-ride weight). To form `mask`, add some person $i$ to `mask \ {i}`: if $i$ fits in the current last ride, keep the ride count and increase its weight; otherwise start a new ride carrying only $i$. The answer is the ride count of the full set.

对人的子集做位掩码 DP。对每个子集 `mask` 存一个二元组 $dp[\text{mask}] = (\text{乘坐次数}, \text{最后一次乘坐的重量})$，取尽量小（先比次数，再比最后一次的重量）。要构造 `mask`，把某个人 $i$ 加到 `mask \ {i}` 上：若 $i$ 能装进当前最后一次乘坐，则保持次数并增加其重量；否则新开一次只载 $i$。答案为全集的乘坐次数。

## Complexity / 复杂度

There are $2^n$ subsets each trying $n$ people, so the time is $O(n \cdot 2^n)$.

共 $2^n$ 个子集、每个尝试 $n$ 个人，因此时间为 $O(n \cdot 2^n)$。
