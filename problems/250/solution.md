# 250 - Knuth Division

## Problem / 题目
Repeatedly split the array into single elements; each split of a subarray costs the sum of its values. Minimize the total cost.

反复把数组分割成单个元素；每次分割某子数组的代价为其元素之和。最小化总代价。

## Idea / 思路
Let $dp[i][j]$ be the minimum cost to fully split the subarray $[i,j]$. Then $dp[i][j]=\text{sum}(i,j)+\min_{i\le t<j}\big(dp[i][t]+dp[t+1][j]\big)$. This interval DP satisfies Knuth's quadrangle conditions, so the optimal split point is monotonic: $\text{opt}[i][j-1]\le\text{opt}[i][j]\le\text{opt}[i+1][j]$, reducing the total work to $O(n^2)$.

设 $dp[i][j]$ 为完全分割子数组 $[i,j]$ 的最小代价。则 $dp[i][j]=\text{sum}(i,j)+\min_{i\le t<j}\big(dp[i][t]+dp[t+1][j]\big)$。该区间 DP 满足 Knuth 四边形条件，最优分割点单调：$\text{opt}[i][j-1]\le\text{opt}[i][j]\le\text{opt}[i+1][j]$，使总工作量降为 $O(n^2)$。

## Complexity / 复杂度
$O(n^2)$. $O(n^2)$。
