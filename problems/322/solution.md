# 322 - New Flight Routes

## Problem / 题目
Add the minimum number of one-way flights to make a directed graph strongly connected, and output them.

加最少的单向航线使有向图强连通，并输出这些航线。

## Idea / 思路
Condense into SCCs. If only one SCC, the answer is $0$. Otherwise (Eswaran–Tarjan) the answer is $\max(s,t)$, where $s$ and $t$ are the numbers of source and sink SCCs in the condensation. Construction: greedily pair each source with a reachable, unused sink via a single DFS; chain the pairs into one cycle by adding $\text{sink}_i \to \text{source}_{i+1}$. Then integrate leftovers — pair a leftover sink with a leftover source by an arc (it absorbs both into the big SCC at once), and attach any remaining sources/sinks to a hub of the cycle.

缩点为 SCC。若仅一个 SCC，答案为 $0$。否则（Eswaran–Tarjan）答案为 $\max(s,t)$，$s,t$ 为缩点图中源、汇 SCC 的个数。构造：用一次 DFS 把每个源贪心配一个可达且未用的汇；加 $\text{sink}_i\to\text{source}_{i+1}$ 把各对连成一个环。再处理剩余——用一条弧把剩余汇与剩余源配对（一条弧同时把两者并入大 SCC），其余多出的源/汇接到环上的枢纽。

## Multi-solution / 多解
Any minimum augmentation is accepted; the checker recomputes $\max(s,t)$ and verifies the augmented graph is a single SCC.

任意最小加边方案均可；checker 重算 $\max(s,t)$ 并验证加边后为单一 SCC。

## Complexity / 复杂度
$O(n+m)$. $O(n+m)$。
