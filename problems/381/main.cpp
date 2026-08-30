#include <bits/stdc++.h>
using namespace std;

// 381 Coin Grid: minimum vertex cover in a bipartite graph (rows vs columns,
// edge = a coin) via Kőnig's theorem: min vertex cover size = max matching size.
// Construct the cover from the matching using the standard alternating-path trick.

static int n;
static vector<int> adjRow[105];
static int matchRow[105], matchCol[105];
static bool used[105];

bool tryKuhn(int r) {
    for (int c : adjRow[r]) {
        if (used[c]) continue;
        used[c] = true;
        if (matchCol[c] == -1 || tryKuhn(matchCol[c])) {
            matchCol[c] = r;
            matchRow[r] = c;
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    vector<string> g(n);
    for (auto &row : g) {
        char buf[105];
        scanf("%s", buf);
        row = buf;
    }
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (g[r][c] == 'o') adjRow[r].push_back(c);

    memset(matchRow, -1, sizeof(matchRow));
    memset(matchCol, -1, sizeof(matchCol));
    for (int r = 0; r < n; r++) {
        memset(used, false, sizeof(used));
        tryKuhn(r);
    }

    // Kőnig's construction: alternate-path reachability from unmatched rows.
    vector<bool> visRow(n, false), visCol(n, false);
    queue<int> q;
    for (int r = 0; r < n; r++)
        if (matchRow[r] == -1) { visRow[r] = true; q.push(r); }
    while (!q.empty()) {
        int r = q.front(); q.pop();
        for (int c : adjRow[r]) {
            if (visCol[c]) continue;
            visCol[c] = true;
            int r2 = matchCol[c];
            if (r2 != -1 && !visRow[r2]) { visRow[r2] = true; q.push(r2); }
        }
    }

    vector<pair<int,int>> res; // (1,row) or (2,col), 1-indexed
    for (int r = 0; r < n; r++) if (!visRow[r]) res.push_back({1, r + 1});
    for (int c = 0; c < n; c++) if (visCol[c]) res.push_back({2, c + 1});

    printf("%d\n", (int)res.size());
    for (auto &p : res) printf("%d %d\n", p.first, p.second);
}
