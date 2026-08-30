# 028 - Concert Tickets

## Problem / 题目

There are $n$ tickets with prices. Each of $m$ customers, in order, buys the ticket with the highest price not exceeding their maximum; that ticket is then removed. Print each customer's price, or $-1$ if none is affordable.

有 $n$ 张带价格的票。$m$ 个顾客依次到来，每人买一张价格不超过其上限的最贵的票，该票随即被买走。输出每位顾客付的价格，若无可买的票则输出 $-1$。

## Idea / 思路

Keep the ticket prices in a `multiset`. For a customer with limit $t$, `upper_bound(t)` gives the first ticket strictly greater than $t$; the element just before it is the most expensive ticket $\le t$. Erase that element and print it; if `upper_bound` is already at the beginning, no ticket is affordable so print $-1$.

把票价放进一个 `multiset`。对上限为 $t$ 的顾客，`upper_bound(t)` 给出第一张严格大于 $t$ 的票，它前面那张就是不超过 $t$ 的最贵票。删除并输出它；若 `upper_bound` 已在开头，说明没有可买的票，输出 $-1$。

## Complexity / 复杂度

Each query does an $O(\log n)$ search and erase, so the total is $O((n + m) \log n)$.

每次查询做一次 $O(\log n)$ 的查找与删除，因此总计 $O((n + m) \log n)$。
