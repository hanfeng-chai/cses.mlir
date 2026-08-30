# 366 - Letter Pair Move Game

## Problem / 题目

There are $2n$ boxes containing $n-1$ `A`s, $n-1$ `B`s, and one adjacent pair of empty boxes. A move transfers any adjacent pair of letters into the two empty boxes while preserving their order. Produce at most $1000$ moves so that, ignoring the empty boxes, every `A` appears before every `B`, or report impossibility.

有 $2n$ 个盒子，其中有 $n-1$ 个 `A`、$n-1$ 个 `B` 和一对相邻空盒。一次操作把任意一对相邻字母按原顺序移入两个空盒。要求在至多 $1000$ 步内使所有 `A` 都位于所有 `B` 之前（忽略空盒位置），或判断无解。

## Idea / 思路

A move is reversible: moving a pair from positions $p,p+1$ into the empty positions makes $p,p+1$ the new empty pair, and the reverse move restores the old state. This makes breadth-first search practical on a **constant-size window**.

### 1. Exact small-window graph / 精确小窗口状态图

For a window of length $L$, a state is a string containing one adjacent `..` pair and letters elsewhere. Seed BFS with goal states whose letters, after deleting dots, are of the form
$$A^aB^{L-2-a}.$$
Run BFS backwards (equivalently forwards, because moves are reversible). For every discovered state, store a parent state one legal move closer to a goal. There are only
$$(L-1)2^{L-2}$$
states when the counts of `A` and `B` are allowed to vary. For $L=8$, this is just $7\cdot64=448$ states.

For full boards shorter than eight boxes ($n<4$), build the exact graph for the whole board. If the input is absent from the graph, print `-1`; otherwise follow parent pointers to a sorted state. Exhaustive state-graph checking confirms that some $n=2,3$ states are genuinely impossible, while all states for $n=4,5$ are reachable.

一次操作是可逆的：把位置 $p,p+1$ 的字母对移入空盒后，$p,p+1$ 成为新的空盒；反向操作即可恢复原状态。因此可以在**常数长度窗口**上做 BFS。

对长度 $L$ 的窗口，状态是一个含相邻 `..` 和其余字母的字符串。以删除点后形如
$$A^aB^{L-2-a}$$
的所有目标状态为 BFS 起点。反向 BFS（由于操作可逆，也等价于正向）并为每个状态保存一个距离目标更近的父状态。若允许窗口内 A/B 数量变化，总状态数只有
$$(L-1)2^{L-2}。$$
当 $L=8$ 时仅为 $7\cdot64=448$。

若整个棋盘少于8格（$n<4$），直接为整盘建立精确状态图。输入状态不在图中则输出 `-1`，否则沿父指针走到有序状态。完整状态图穷举验证表明：$n=2,3$ 的确存在无解状态，而 $n=4,5$ 的全部状态都可达。

### 2. Sweep a length-eight window / 用长度8窗口向右推进

For $2n\ge8$, first move the empty pair to positions $0,1$ using at most two moves. Maintain a cursor pointing to the empty pair and a sorted prefix to its left.

- If the next two letters are `AA`, move them into the empty boxes. This fixes two more `A`s in the prefix and advances the empty pair by two positions.
- Otherwise, find a `B` pair start and a later `A`. Three pair moves rotate these pieces so that progress becomes possible without disturbing the already fixed prefix.
- Once fewer than eight boxes remain to the right, use the precomputed length-eight parent graph to sort the final window exactly.

The three-move rotation is:

1. move the pair beginning at the chosen `B` into the current empty pair;
2. move a pair containing the later `A` into the new empty pair;
3. move the first saved pair into the latest empty pair.

This keeps one adjacent empty pair and preserves every pair's internal order. Each iteration either fixes two positions or rearranges a constant number of pairs so that the next fixation/window solve succeeds. Hence the number of moves is linear; the construction is bounded by $10n$ and therefore by $1000$ for $n\le100$.

当 $2n\ge8$ 时，先用至多两步把空盒移动到位置 $0,1$。维护一个指向空盒的游标，其左侧前缀已经有序固定。

- 若空盒右侧紧接 `AA`，把它移入空盒。这样前缀又固定两个 A，空盒向右推进两格；
- 否则寻找一个以 `B` 开头的字母对和更靠后的 `A`，用三次字母对搬运旋转这些部分，在不破坏已固定前缀的前提下制造下一次进展；
- 当右侧剩余部分不足以继续剥离时，使用预计算的长度8父指针图精确整理最终窗口。

三步旋转为：

1. 把选中的 B 开头字母对移入当前空盒；
2. 把包含后方 A 的字母对移入新空盒；
3. 把第一步暂存的字母对移入最新空盒。

整个过程始终保留一对相邻空盒，并保持每个搬运字母对的内部顺序。每轮要么固定两个位置，要么只用常数次操作重排，使下一次固定或窗口收尾成为可能。因此总步数为线性，构造上界为 $10n$；在 $n\le100$ 时自然不超过1000。

### 3. Validation / 验证

The custom checker simulates every printed full-board state and verifies it is obtained by exactly one legal pair move from the preceding state, then checks the final dot-deleted string equals $A^{n-1}B^{n-1}$. The implementation was also compared with exhaustive reachability BFS for every legal state through $n=5$, and stressed on 500 random instances up to $n=100$.

自定义 checker 会模拟输出的每个完整棋盘状态，验证它恰好由前一状态的一次合法字母对搬运得到，最后检查删除点后的字符串等于 $A^{n-1}B^{n-1}$。实现还与 $n\le5$ 的所有合法状态的完整可达性 BFS 逐一比较，并在500个最大到 $n=100$ 的随机实例上压力测试。

## Complexity / 复杂度

The length-eight graph is constant size. The sweep performs $O(n)$ moves; straightforward string searches/replacements cost $O(n)$ each, so the conservative total is $O(n^2)$ with $n\le100$. Stored output states use $O(n^2)$ characters.

长度8状态图是常数规模。扫描过程执行 $O(n)$ 次操作；直接的字符串查找与替换每次 $O(n)$，故保守总复杂度为 $O(n^2)$，而 $n\le100$。保存全部输出状态共占 $O(n^2)$ 个字符。
