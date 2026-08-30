# 120 - Static Range Minimum Queries

## Problem / 题目

Given a static array, answer $q$ queries each asking the minimum value in a range $[a,b]$.

给定一个静态数组，回答 $q$ 个询问，每个问区间 $[a,b]$ 的最小值。

## Idea / 思路

Build a **sparse table**: $sp[j][i]$ stores the minimum of the block of length $2^j$ starting at $i$, computed by $sp[j][i] = \min(sp[j-1][i], sp[j-1][i+2^{j-1}])$. A query $[a,b]$ is covered by two overlapping blocks of length $2^k$ where $k = \lfloor \log_2(b-a+1) \rfloor$, so the answer is $\min(sp[k][a],\, sp[k][b-2^k+1])$. Overlap is fine because minimum is idempotent.

构建**稀疏表**：$sp[j][i]$ 存以 $i$ 开头、长度 $2^j$ 的块的最小值，递推 $sp[j][i] = \min(sp[j-1][i], sp[j-1][i+2^{j-1}])$。询问 $[a,b]$ 由两个长度 $2^k$ 的重叠块覆盖，$k = \lfloor \log_2(b-a+1) \rfloor$，故答案为 $\min(sp[k][a],\, sp[k][b-2^k+1])$。重叠无妨，因为最小值幂等。

## Complexity / 复杂度

Building is $O(n\log n)$ and each query is $O(1)$.

构建 $O(n\log n)$，每个询问 $O(1)$。
