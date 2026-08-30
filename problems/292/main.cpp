#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    int n; scanf("%d", &n);
    if (n <= 3) { printf("IMPOSSIBLE\n"); return 0; }
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) g[i][j] = (i + j) % n + 1;  // Latin square (each value n times)
    vector<ll> S(2 * n, 0);  // slots: 0..n-1 rows, n..2n-1 cols
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) { S[i] += g[i][j]; S[n + j] += g[i][j]; }
    unordered_map<ll, int> freq; freq.reserve(4 * n);
    ll coll = 0;
    auto add = [&](ll v) { int &f = freq[v]; if (f >= 1) coll++; f++; };
    auto rem = [&](ll v) { int &f = freq[v]; f--; if (f >= 1) coll--; };
    for (int s = 0; s < 2 * n; s++) add(S[s]);
    mt19937 rng(998244353);
    ll iter = 0, cap = (ll)40 * n * n + 2000000;
    while (coll > 0 && iter < cap) {
        iter++;
        int i1 = rng() % n, j1 = rng() % n, i2 = rng() % n, j2 = rng() % n;
        int a = g[i1][j1], b = g[i2][j2];
        if (a == b) continue;
        // net deltas on affected slots
        int sl[4] = {i1, i2, n + j1, n + j2};
        ll dl[4] = {b - a, a - b, b - a, a - b};
        // dedup
        ll oldColl = coll;
        // apply
        for (int t = 0; t < 4; t++) if (dl[t]) { rem(S[sl[t]]); S[sl[t]] += dl[t]; add(S[sl[t]]); }
        g[i1][j1] = b; g[i2][j2] = a;
        bool accept = coll <= oldColl || (rng() % 100 < 3);
        if (!accept) {  // revert
            for (int t = 0; t < 4; t++) if (dl[t]) { rem(S[sl[t]]); S[sl[t]] -= dl[t]; add(S[sl[t]]); }
            g[i1][j1] = a; g[i2][j2] = b;
        }
    }
    string out;
    for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) { out += to_string(g[i][j]); out += " \n"[j == n - 1]; } }
    cout << out;
}
