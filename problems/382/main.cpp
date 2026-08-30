#include <bits/stdc++.h>
using namespace std;

// 382 Grid Coloring II: every cell must change to a color different from its
// original AND from all (up to 4) grid-adjacent cells. Each cell has exactly 2
// allowed colors (the 2 it wasn't already showing) -- this is a classic 2-SAT:
// variable x_i = true means "cell i picks its first allowed color", false means
// "its second". For every adjacent pair (i,j) and every pair of choices (a,b)
// whose resulting colors coincide, add a clause forbidding that combination.
// Solve via Tarjan SCC on the implication graph; if some cell's two literals
// land in the same SCC, no coloring exists.
int n, m;
vector<string> grid;
int N;

inline int cellId(int r, int c) { return r * m + c; }

vector<pair<int,int>> adjList; // literal implication edges (u -> v)
vector<vector<int>> g, rg;

inline int negLit(int x) { return x ^ 1; }

void addClause(int u, int v) {
    g[negLit(u)].push_back(v);
    g[negLit(v)].push_back(u);
}

// Tarjan SCC
vector<int> comp, low, num, stkArr;
vector<bool> onStk;
int timer_, compCnt, sp;

void tarjan(int u) {
    // iterative Tarjan to avoid recursion-depth issues for large grids
    vector<int> callStack, idxStack;
    callStack.push_back(u);
    idxStack.push_back(0);
    num[u] = low[u] = timer_++;
    stkArr[sp++] = u;
    onStk[u] = true;
    while (!callStack.empty()) {
        int node = callStack.back();
        int &idx = idxStack.back();
        if (idx < (int)g[node].size()) {
            int to = g[node][idx++];
            if (num[to] == -1) {
                num[to] = low[to] = timer_++;
                stkArr[sp++] = to;
                onStk[to] = true;
                callStack.push_back(to);
                idxStack.push_back(0);
            } else if (onStk[to]) {
                low[node] = min(low[node], num[to]);
            }
        } else {
            callStack.pop_back();
            idxStack.pop_back();
            if (!callStack.empty()) {
                int parent = callStack.back();
                low[parent] = min(low[parent], low[node]);
            }
            if (low[node] == num[node]) {
                while (true) {
                    int x = stkArr[--sp];
                    onStk[x] = false;
                    comp[x] = compCnt;
                    if (x == node) break;
                }
                compCnt++;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    grid.resize(n);
    for (auto &row : grid) {
        char buf[505];
        scanf("%s", buf);
        row = buf;
    }
    N = n * m;
    g.assign(2 * N, {});

    auto options = [&](char orig) -> array<char,2> {
        array<char,2> res;
        int k = 0;
        for (char c : {'A','B','C'}) if (c != orig) res[k++] = c;
        return res;
    };

    int dr[2] = {0, 1}, dc[2] = {1, 0}; // only need right & down; each edge counted once
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int i = cellId(r, c);
            auto oi = options(grid[r][c]);
            for (int d = 0; d < 2; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr >= n || nc >= m) continue;
                int j = cellId(nr, nc);
                auto oj = options(grid[nr][nc]);
                for (int a = 0; a < 2; a++)
                    for (int b = 0; b < 2; b++)
                        if (oi[a] == oj[b]) {
                            // forbid (i picks oi[a]) AND (j picks oj[b])
                            addClause(2 * i + (1 - a), 2 * j + (1 - b));
                        }
            }
        }
    }

    int V = 2 * N;
    comp.assign(V, -1);
    low.assign(V, 0);
    num.assign(V, -1);
    stkArr.assign(V, 0);
    onStk.assign(V, false);
    timer_ = 0; compCnt = 0; sp = 0;
    for (int v = 0; v < V; v++) if (num[v] == -1) tarjan(v);

    vector<char> chosen(N);
    bool ok = true;
    for (int i = 0; i < N && ok; i++) {
        if (comp[2 * i] == comp[2 * i + 1]) { ok = false; break; }
        // Tarjan assigns component ids in reverse topological order of the DAG
        // of SCCs (id 0 = a "sink"); picking the literal whose component id is
        // SMALLER means picking the one that is later in topological order,
        // which is the standard rule for a consistent 2-SAT assignment.
        bool chooseOpt0 = comp[2 * i] < comp[2 * i + 1];
        char orig = grid[i / m][i % m];
        auto oi = options(orig);
        chosen[i] = chooseOpt0 ? oi[0] : oi[1];
    }

    if (!ok) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) putchar(chosen[cellId(r, c)]);
        putchar('\n');
    }
}
