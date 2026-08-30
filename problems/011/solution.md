# 011 - Coin Piles

## Problem / 题目

We have two piles with $a$ and $b$ coins. In one move we remove **either** $1$ coin from the first pile and $2$ from the second, **or** $2$ from the first and $1$ from the second. For each test, decide whether both piles can be emptied.

有两堆硬币，分别是 $a$ 和 $b$ 个。每次操作要么从第一堆拿 $1$ 个、第二堆拿 $2$ 个，要么从第一堆拿 $2$ 个、第二堆拿 $1$ 个。对每组数据判断能否把两堆都清空。

## Idea / 思路

Let $x$ be the number of moves of the first type and $y$ the number of the second type. Then $a = x + 2y$ and $b = 2x + y$. Adding the two equations gives $a + b = 3(x + y)$, so $3$ must divide $a + b$. Solving the system yields $x = (2b - a)/3$ and $y = (2a - b)/3$, both of which must be non-negative, i.e. $a \le 2b$ and $b \le 2a$. These three conditions together are necessary and sufficient.

设第一类操作做 $x$ 次、第二类做 $y$ 次，则 $a = x + 2y$、$b = 2x + y$。两式相加得 $a + b = 3(x + y)$，所以 $3$ 必须整除 $a + b$。解这个方程组得 $x = (2b - a)/3$、$y = (2a - b)/3$，二者都必须非负，即 $a \le 2b$ 且 $b \le 2a$。这三个条件合在一起既必要又充分。

## Complexity / 复杂度

Each test is answered with a constant number of arithmetic operations, so the time is $O(1)$ per query.

每组数据只用常数次算术运算即可判定，因此每次查询是 $O(1)$。
