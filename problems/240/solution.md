# 240 - Cut and Paste

## Problem / 题目
Process operations that cut a substring $[a,b]$ and paste it to the end of the string. Output the final string.

处理「剪切子串 $[a,b]$ 并粘贴到串尾」的操作。输出最终字符串。

## Idea / 思路
Represent the string with an implicit treap (a balanced BST keyed by position) supporting split and merge in $O(\log n)$. To cut $[a,b]$, split the tree into three parts $A=[1,a-1]$, $M=[a,b]$, $R=[b+1,n]$, then merge them as $A+R+M$. An in-order traversal at the end yields the final string.

用隐式 treap（按位置维护的平衡二叉搜索树）表示字符串，支持 $O(\log n)$ 的 split 与 merge。剪切 $[a,b]$：把树分成三段 $A=[1,a-1]$、$M=[a,b]$、$R=[b+1,n]$，再按 $A+R+M$ 合并。最后中序遍历得到最终串。

## Complexity / 复杂度
$O((n+m)\log n)$. $O((n+m)\log n)$。
