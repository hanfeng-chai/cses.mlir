# 029 - Restaurant Customers

## Problem / 题目

Given the arrival and leaving times of $n$ customers, find the maximum number of customers present at the same time.

给定 $n$ 位顾客的到达与离开时间，求同一时刻在场顾客的最大数量。

## Idea / 思路

Turn each customer into two events: $+1$ at the arrival time and $-1$ at the leaving time. Sort all events by time and sweep through them, keeping a running count of customers currently inside; the maximum value this count reaches is the answer. (Sorting puts a leaving before an arrival at the same instant, which is the safe order, though here all times are distinct.)

把每位顾客拆成两个事件：到达时刻 $+1$、离开时刻 $-1$。把所有事件按时间排序后扫描，维护当前在场人数的累加值；这个值达到的最大就是答案。（排序让同一时刻的离开排在到达之前，这是安全的顺序，尽管本题所有时间互不相同。）

## Complexity / 复杂度

Sorting $2n$ events dominates, giving $O(n \log n)$.

对 $2n$ 个事件排序是主要开销，为 $O(n \log n)$。
