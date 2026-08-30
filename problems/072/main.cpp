#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (auto &r : g) cin >> r;
    string res;
    res.push_back(g[0][0]);
    vector<char> active(n, 0);
    active[0] = 1;  // diagonal 0: only cell (0,0)
    for (int d = 1; d <= 2 * n - 2; d++) {
        vector<char> cand(n, 0);
        for (int i = 0; i < n; i++)
            if (active[i]) {
                int j = (d - 1) - i;
                if (i + 1 < n) cand[i + 1] = 1;       // move down
                if (j + 1 < n) cand[i] = 1;           // move right
            }
        char best = 127;
        for (int i = 0; i < n; i++)
            if (cand[i]) { int j = d - i; if (j >= 0 && j < n) best = min(best, g[i][j]); }
        vector<char> nxt(n, 0);
        for (int i = 0; i < n; i++)
            if (cand[i]) { int j = d - i; if (j >= 0 && j < n && g[i][j] == best) nxt[i] = 1; }
        res.push_back(best);
        active = move(nxt);
    }
    cout << res << "\n";
}
