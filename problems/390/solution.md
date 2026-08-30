# 390 - Reversal Sorting

## Problem / 题目

Given a permutation of $1,\dots,n$, sort it using at most $n$ subarray reversals; print any valid sequence of reversals.

给定 $1,\dots,n$ 的一个排列，用不超过 $n$ 次子数组反转把它排好序；输出任意一种合法方案。

## Idea / 思路

**Selection sort by reversal.** For $i=1,\dots,n$: find the current position $\mathrm{pos}$ of value $i$; if $\mathrm{pos}\ne i$, reverse the segment $[i,\mathrm{pos}]$, which brings value $i$ to position $i$ (and never disturbs positions $1,\dots,i-1$, which already hold $1,\dots,i-1$). This uses at most $n-1\le n$ reversals.

**Why a plain array simulation is too slow.** Physically reversing $[i,\mathrm{pos}]$ costs $O(\mathrm{pos}-i)$. This looks cheap on average, but an adversarial permutation (e.g. rotating the array by $n/2$) makes $\Theta(n)$ of the reversals each have length $\Theta(n)$, giving $\Theta(n^2)$ total work — too slow for $n\le 2\times10^5$.

**Implicit treap.** Maintain the array as an order-statistics BST ("treap") ordered by *current position* rather than by value, with a lazy "reversed" flag per subtree (the standard trick for $O(\log n)$ range-reversal). Each value $v$'s tree node is created once and never destroyed, so a `nodeOf[v]` pointer always identifies it; what changes is only its position within the tree. Two operations are needed:
- **`split`/`merge` by rank** — the classic treap building blocks, used to cut out the segment $[i,\mathrm{pos}]$, flip its lazy reversed-flag, and splice it back.
- **`rankOf(node)`** — find a specific node's current rank without knowing it in advance. This is done by walking from the node up to the root via parent pointers.

**A subtle correctness pitfall.** It's tempting to compute a node's effective side (left/right) relative to each ancestor using *only that ancestor's own* `rev` flag while walking bottom-up, skipping any push-down (reasoning: "a flag only describes that node's own stored children, so it shouldn't need pushing down just to answer which side a child is on"). This checks out on small hand-traced 2–3 level examples but is **provably not enough** for deeper trees — verified experimentally: it produced nonsensical results (a value's reported position smaller than its already-fixed index) on random permutations as small as $n=10$. The fix that is unconditionally correct: first collect the path from the node up to the root, then push down along that path from the *root end* towards the node (so every ancestor's rev flag is resolved into actual swapped left/right pointers *before* any comparison is made), and only then do the simple bottom-up rank sum using plain `cur == parent->right` checks. This keeps the whole operation $O(\log n)$ (the path has expected $O(\log n)$ length for a random-priority treap) while being straightforward to prove correct.

**选择排序 + 反转。** 对 $i=1,\dots,n$：找到值 $i$ 当前所在的位置 $\mathrm{pos}$；若 $\mathrm{pos}\ne i$，反转区间 $[i,\mathrm{pos}]$，这会把值 $i$ 带到位置 $i$（并且不会打乱已经放好 $1,\dots,i-1$ 的前缀）。总共最多用 $n-1\le n$ 次反转。

**为什么直接模拟数组太慢。** 物理反转 $[i,\mathrm{pos}]$ 的代价是 $O(\mathrm{pos}-i)$。平均看起来很便宜，但一个刻意构造的排列（比如把数组整体循环移位 $n/2$）会让 $\Theta(n)$ 次反转每次长度都是 $\Theta(n)$，总代价 $\Theta(n^2)$——对 $n\le2\times10^5$ 而言太慢。

**隐式 Treap。** 把数组维护成一棵按**当前位置**（而非数值）排序的顺序统计 BST（"Treap"），每个子树带一个懒惰的"已反转"标记（区间反转的标准技巧）。每个数值 $v$ 对应的树节点只创建一次，从不销毁，因此 `nodeOf[v]` 指针始终有效；变化的只是它在树中的位置。需要两个操作：
- **按排名 `split`/`merge`**——经典 Treap 组件，用来把区间 $[i,\mathrm{pos}]$ 切下来、翻转其懒惰反转标记、再拼回去。
- **`rankOf(node)`**——在不预先知道排名的情况下，求某个具体节点当前的排名，通过父指针从该节点走到根来实现。

**一个隐蔽的正确性陷阱。** 很容易想：自底向上走的时候，判断某节点相对某个祖先是"左"还是"右"，只需要看**那个祖先自己的** `rev` 标记（理由是"标记只描述自己存储的子节点，不该需要下推就能知道某个孩子在哪一侧"），跳过下推。这在手工验证的2~3层小例子上是对的，但对更深的树**被证明是不够的**——实测验证：在随机生成的 $n=10$ 排列上就出现了荒谬的结果（某个值汇报的位置比已经固定好的下标还小）。始终正确的修正方法：先收集从该节点到根的路径，再沿这条路径**从根端往节点端**依次下推（这样每个祖先的 rev 标记都先被解析成真实交换后的左右指针），然后再用普通的 `cur == parent->right` 判断做自底向上求和。这样整体仍是 $O(\log n)$（随机优先级 Treap 的路径长度期望为 $O(\log n)$），且正确性容易证明。

## Complexity / 复杂度

Each of the $n$ selection steps does $O(\log n)$ work for `rankOf` plus $O(\log n)$ for the split/merge-based reversal, giving $O(n\log n)$ overall for $n\le 2\times10^5$.

$n$ 次选择每步都是 `rankOf` 的 $O(\log n)$ 加上 split/merge 反转的 $O(\log n)$，整体 $O(n\log n)$，$n\le2\times10^5$ 内足够快。
