# 297 - Tree Traversals

## Problem / 题目
Given the preorder and inorder traversals of a binary tree, output its postorder traversal.

给定二叉树的前序与中序遍历，输出其后序遍历。

## Idea / 思路
Reconstruct the tree in $O(n)$ with the classic stack method: scan the preorder, pushing nodes; when the stack top matches the current inorder element, pop while it matches and attach the next preorder node as a right child, otherwise as a left child. Then emit postorder iteratively to avoid deep recursion.

用经典栈法 $O(n)$ 重建：扫描前序压栈；当栈顶等于当前中序元素时，持续弹出并把下一前序结点接为右孩子，否则接为左孩子。随后迭代输出后序以避免深递归。

## Complexity / 复杂度
$O(n)$. $O(n)$。
