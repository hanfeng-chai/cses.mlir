#include <bits/stdc++.h>
using namespace std;
const int MX = 200005;
int len_[MX], link_[MX], to[MX][26], sz = 1, last = 1;
long long occ[MX];
void ext(int c) {
    int cur = ++sz; len_[cur] = len_[last] + 1; occ[cur] = 1; int p = last;
    while (p && !to[p][c]) { to[p][c] = cur; p = link_[p]; }
    if (!p) link_[cur] = 1;
    else {
        int q = to[p][c];
        if (len_[q] == len_[p] + 1) link_[cur] = q;
        else {
            int cl = ++sz; len_[cl] = len_[p] + 1; link_[cl] = link_[q]; occ[cl] = 0;
            memcpy(to[cl], to[q], sizeof(to[q]));
            while (p && to[p][c] == q) { to[p][c] = cl; p = link_[p]; }
            link_[q] = cl; link_[cur] = cl;
        }
    }
    last = cur;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; long long k; cin >> s >> k; int n = s.size();
    for (char ch : s) ext(ch - 'a');
    vector<int> ord(sz + 1), bk(n + 2, 0);
    for (int v = 1; v <= sz; v++) bk[len_[v]]++;
    for (int i = 1; i <= n; i++) bk[i] += bk[i - 1];
    for (int v = 1; v <= sz; v++) ord[bk[len_[v]]--] = v;
    for (int i = sz; i >= 1; i--) { int v = ord[i]; if (link_[v]) occ[link_[v]] += occ[v]; }  // endpos sizes
    vector<long long> f(sz + 1, 0);  // f[v] = total occurrences-weighted substrings under v
    for (int i = sz; i >= 1; i--) { int v = ord[i]; for (int c = 0; c < 26; c++) if (to[v][c]) { int u = to[v][c]; f[v] += occ[u] + f[u]; } }
    string res; int v = 1;
    while (true) {
        bool moved = false;
        for (int c = 0; c < 26; c++) if (to[v][c]) {
            int u = to[v][c]; long long block = occ[u] + f[u];
            if (k <= block) { res += ('a' + c); if (k <= occ[u]) { cout << res << "\n"; return 0; } k -= occ[u]; v = u; moved = true; break; }
            else k -= block;
        }
        if (!moved) break;
    }
    cout << res << "\n";
}
