# 277 - Maximum Xor Subarray

## Problem / 题目
Find the maximum xor of any subarray.

求任意子数组的最大异或和。

## Idea / 思路
A subarray xor equals $\text{px}[j]\oplus\text{px}[i]$ for prefix xors. Insert prefix xors into a binary trie; for each new prefix xor, walk the trie preferring the opposite bit at each level to maximize the xor with a previously inserted value. The best over all pairs is the answer.

子数组异或等于前缀异或的 $\text{px}[j]\oplus\text{px}[i]$。把前缀异或插入二进制 trie；对每个新前缀异或，在 trie 中每层尽量走相反位以最大化与已插入值的异或。所有对的最优即答案。

## Complexity / 复杂度
$O(n\log V)$. $O(n\log V)$。
