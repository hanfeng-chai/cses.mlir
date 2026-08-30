# 188 - Moving Robots

## Problem / 题目
Every square of an $8\times 8$ board starts with a robot. Each robot performs $k$ independent random single-step moves (staying on the board). Print the expected number of empty squares, rounded to six decimals.

$8\times 8$ 棋盘每格各有一个机器人。每个机器人独立走 $k$ 步随机的单格移动（不出界）。输出期望的空格数，保留六位小数。

## Idea / 思路
For each starting square run a $k$-step random-walk DP to get the distribution $P[p][s]$ that the robot starting at $p$ ends on $s$. A square $s$ is empty iff no robot lands there, so by independence $\Pr[s\text{ empty}]=\prod_p (1-P[p][s])$. The answer is the sum over all squares by linearity of expectation.

对每个起点格做 $k$ 步随机游走 DP，得到分布 $P[p][s]$（起点 $p$ 的机器人停在 $s$ 的概率）。格 $s$ 为空当且仅当没有机器人落在其上，由独立性 $\Pr[s\text{ 空}]=\prod_p (1-P[p][s])$。由期望线性性，答案为对所有格求和。

## Complexity / 复杂度
$O(64\cdot k\cdot 64)$. $O(64\cdot k\cdot 64)$。
