# 352 - Special Substrings

## Problem / 题目

A substring is special when every character that appears in the **original input string** occurs equally many times in that substring. Count all special substrings.

若原输入字符串中出现过的**每一种字符**，在某个子串中的出现次数都相等，则该子串是特殊子串。求特殊子串数量。

## Idea / 思路

Let the distinct characters present in the whole string be $C$. For each prefix ending before position $i$, let $P_i[c]$ be the number of occurrences of character $c$ in that prefix. Choose any fixed reference character $r\in C$ and define the prefix fingerprint
$$F_i[c]=P_i[c]-P_i[r]\qquad(c\in C).$$
Coordinates for letters not present globally are kept at zero and ignored.

Consider substring $s[l..r-1]$. Its count of character $c$ is
$$P_r[c]-P_l[c].$$
All globally present characters have equal substring counts exactly when, for every $c\in C$,
$$P_r[c]-P_l[c]=P_r[r_0]-P_l[r_0],$$
where $r_0$ is the chosen reference character. Rearranging gives
$$P_r[c]-P_r[r_0]=P_l[c]-P_l[r_0],$$
which is precisely
$$F_r=F_l.$$

Thus the answer is the number of equal pairs of prefix fingerprints. Scan the string left to right, maintain all prefix character counts, build the current fingerprint, and use a hash table:

- the empty prefix fingerprint occurs once initially;
- if the current fingerprint has appeared $q$ times, it forms $q$ new special substrings ending here;
- then increment its stored frequency.

A nonempty substring between equal fingerprints cannot add zero occurrences of every global character, because every input character belongs to $C$; therefore the common added count is automatically positive.

The wording is easy to misread: it does **not** mean merely “all characters that happen to occur inside this substring have equal frequency.” Under that interpretation every one-character substring would count, contradicting the sample list. It means all characters appearing in the original string must receive the same count in the selected substring.

设原串中不同字符的集合为 $C$。对位置 $i$ 之前的前缀，令 $P_i[c]$ 为字符 $c$ 的出现次数。任取一个固定基准字符 $r\in C$，定义前缀指纹
$$F_i[c]=P_i[c]-P_i[r]\qquad(c\in C)。$$
原串中未出现的字母坐标保持为0，不参与约束。

考虑子串 $s[l..r-1]$，其中字符 $c$ 的数量为
$$P_r[c]-P_l[c]。$$
所有全局出现字符的子串计数相等，当且仅当对每个 $c\in C$ 都有
$$P_r[c]-P_l[c]=P_r[r_0]-P_l[r_0]，$$
其中 $r_0$ 是基准字符。移项得到
$$P_r[c]-P_r[r_0]=P_l[c]-P_l[r_0]，$$
也就是
$$F_r=F_l。$$

因此答案就是相同前缀指纹的配对数量。从左到右扫描字符串，维护所有前缀字符计数并构造当前指纹，用哈希表统计：

- 空前缀指纹初始出现1次；
- 若当前指纹此前出现过 $q$ 次，就新增 $q$ 个在当前位置结束的特殊子串；
- 随后把当前指纹频次加1。

两个相同指纹之间若形成非空子串，不可能对所有全局字符都增加0次，因为输入中的每个字符都属于 $C$；因此相同增加量自动为正。

题意容易误读：它并不是说“只要这个子串内部实际出现的字符频次相等即可”。若如此，每个单字符子串都会合法，与样例列出的答案矛盾。真正含义是：原串中出现过的全部字符，在所选子串中都必须有相同计数。

## Complexity / 复杂度

Each of $n$ prefixes builds and hashes a fixed 26-integer key, so expected time is $O(26n)=O(n)$. The hash table stores at most $n+1$ fingerprints, using $O(26n)=O(n)$ memory.

每个前缀构造并哈希一个固定26整数的键，期望时间复杂度 $O(26n)=O(n)$。哈希表至多保存 $n+1$ 个指纹，占 $O(26n)=O(n)$ 空间。
