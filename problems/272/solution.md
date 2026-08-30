# 272 - K-th Highest Score

## Problem / 题目
Two countries each have $n$ coders with distinct scores, accessible by "the $i$-th highest of a country". Find the $k$-th highest overall using at most $100$ queries.

两国各有 $n$ 名选手、分数互异，可询问「某国第 $i$ 高分」。用至多 $100$ 次询问求全场第 $k$ 高分。

## Idea / 思路
Both countries' scores are sorted descending. Binary search the number $i$ of Finland scores among the global top $k$: find the largest $i$ with Finland's $i$-th score at least Sweden's $(k-i+1)$-th. Then the $k$-th highest is the smaller of Finland's $i$-th and Sweden's $(k-i)$-th. Cache queried values to stay within the limit.

两国分数各自降序。二分全局前 $k$ 中来自芬兰的数量 $i$：求最大的 $i$ 使芬兰第 $i$ 分不小于瑞典第 $(k-i+1)$ 分。则第 $k$ 高分为芬兰第 $i$ 与瑞典第 $(k-i)$ 中较小者。缓存已询问值以控制次数。

## Complexity / 复杂度
$O(\log n)$ queries. $O(\log n)$ 次询问。
