# 023 - String Reorder

## Problem / 题目

Reorder the characters of a string (letters `A`–`Z`) so that no two adjacent characters are equal, producing the **lexicographically minimal** such string, or print `-1` if it is impossible.

重排一个字符串（字母 `A`–`Z`）的字符，使任意相邻两个字符都不相同，并给出**字典序最小**的这种字符串；若不可能则输出 `-1`。

## Idea / 思路

It is impossible exactly when some letter occurs more than $\lceil n/2 \rceil$ times — then it cannot avoid being adjacent to itself. Otherwise build the answer greedily from left to right. At each position, if some letter is so frequent that it *must* be placed now (its remaining count satisfies $2 \cdot cnt > \text{remaining length}$), place that letter; there can be at most one such letter and it is guaranteed to differ from the previous one. Otherwise place the smallest available letter that differs from the previously placed character. This greedy choice yields the lexicographically minimal valid string.

当某个字母出现次数超过 $\lceil n/2 \rceil$ 时无解——它无法避免与自己相邻。否则从左到右贪心构造。在每个位置，若某字母太多以至于*必须*现在放（其剩余数满足 $2 \cdot cnt > \text{剩余长度}$），就放它；这样的字母至多一个，且保证与上一个不同。否则放与上一个字符不同的、最小的可用字母。这个贪心选择给出字典序最小的合法串。

## Complexity / 复杂度

Each of the $n$ positions scans the 26-letter alphabet once, so the time is $O(26\,n)$, fast enough for $n \le 10^6$.

$n$ 个位置每个扫描一遍 26 个字母，因此时间为 $O(26\,n)$，对 $n \le 10^6$ 足够快。
