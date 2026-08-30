# 356 - Water Containers Moves

## Problem / 题目

Containers $A$ (capacity $a$) and $B$ (capacity $b$), both initially empty. Each move fills, empties, or pours between them (a pour always fills or empties at least one side). Find a move sequence ending with exactly $x$ units in $A$ that **minimizes the total amount of water moved**, or report impossibility.

容器 $A$（容量 $a$）与 $B$（容量 $b$），初始都为空。每次操作是灌满、倒空，或把水从一个容器倒进另一个（倒水时必须把某一方灌满或倒空）。求一个操作序列，使 $A$ 最终恰好有 $x$ 单位水，且**移动的总水量最小**，若不可能则报告。

## Idea / 思路

The state is fully described by $(\text{amountInA},\text{amountInB})$, and since $a,b\le1000$ there are at most about $10^6$ states — small enough to build the **entire state graph** explicitly. From any state there are up to $6$ moves (`FILL A`, `FILL B`, `EMPTY A`, `EMPTY B`, `MOVE A B`, `MOVE B A`), each with its own **cost** equal to the amount of water it actually moves (not a uniform cost of $1$!). Since we want to minimize total moved water — a weighted shortest path, not a move count — run **Dijkstra's algorithm** from $(0,0)$ over this graph, then take the minimum distance among all states with $\text{amountInA}=x$ (any amount in $B$). Reconstructing the actual sequence of moves is done by keeping, for every state, which move and predecessor state produced its shortest distance.

If $x>a$, it's trivially impossible (container $A$ can never hold more than its own capacity).

Because several different move sequences can tie for the same minimum total, this problem uses a custom checker: it re-simulates the printed sequence, checks every move is legal and moves a positive amount, confirms the final amount in $A$ is $x$, and compares the declared/optimal total against the jury's value — rather than requiring an exact match to one fixed sequence.

状态完全由 $(A\text{中的水量},B\text{中的水量})$ 描述，由于 $a,b\le1000$，状态总数至多约 $10^6$——足够小，可以直接把**整个状态图**建出来。从任意状态出发最多有 $6$ 种操作（`FILL A`、`FILL B`、`EMPTY A`、`EMPTY B`、`MOVE A B`、`MOVE B A`），每种操作都有自己的**代价**，等于它实际移动的水量（不是统一的代价 $1$！）。既然要最小化移动的总水量——这是带权最短路，不是操作步数——就从 $(0,0)$ 出发跑一次**Dijkstra 算法**，然后在所有 $\text{amountInA}=x$（$B$ 中水量任意）的状态里取最小距离。重建实际操作序列的方法是：为每个状态记录是哪个操作、从哪个前驱状态得到了它的最短距离。

若 $x>a$，显然不可能（容器 $A$ 永远装不下超过自身容量的水）。

由于可能有多种不同的操作序列都能取到同样的最小总水量，本题用自定义 checker 评测：重新模拟输出的操作序列，检查每一步都合法且移动了正数水量，确认 $A$ 最终水量恰为 $x$，并把声明/最优总量与裁判的值比较——而不要求与某个固定序列完全一致。

## Complexity / 复杂度

$O(ab\log(ab))$ for Dijkstra over the $O(ab)$-state, $O(ab)$-edge graph (each state has $O(1)$ outgoing edges). With $a,b\le1000$ this is comfortably fast.

Dijkstra 跑在 $O(ab)$ 个状态、$O(ab)$ 条边（每个状态出边数 $O(1)$）的图上，复杂度 $O(ab\log(ab))$。$a,b\le1000$ 时运行很快。
