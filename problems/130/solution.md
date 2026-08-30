# 130 - Pizzeria Queries

## Problem / 题目

Each building $k$ has a pizza price $p_k$; ordering from building $a$ to $k$ costs $p_a + |a-k|$. Process updates of a price and queries for the cheapest pizza deliverable to building $k$.

每栋楼 $k$ 有比萨价 $p_k$；从楼 $a$ 送到 $k$ 花费 $p_a + |a-k|$。处理价格更新与"送到楼 $k$ 的最便宜比萨"询问。

## Idea / 思路

Split the absolute value by direction. For $a \le k$ the cost is $(p_a - a) + k$; for $a \ge k$ it is $(p_a + a) - k$. So maintain two **segment trees of minimums**: one over $p_a - a$ and one over $p_a + a$. A query takes the minimum of $(p_a-a)$ over the prefix $[1,k]$ plus $k$, and the minimum of $(p_a+a)$ over the suffix $[k,n]$ minus $k$. Updates touch one leaf in each tree.

按方向拆开绝对值。$a \le k$ 时花费 $(p_a - a) + k$；$a \ge k$ 时为 $(p_a + a) - k$。于是维护两棵**最小值线段树**：一棵存 $p_a - a$、一棵存 $p_a + a$。询问取前缀 $[1,k]$ 上 $(p_a-a)$ 的最小值加 $k$，与后缀 $[k,n]$ 上 $(p_a+a)$ 的最小值减 $k$，二者取小。更新各改一棵树的一个叶子。

## Complexity / 复杂度

Every operation is $O(\log n)$.

每个操作 $O(\log n)$。
