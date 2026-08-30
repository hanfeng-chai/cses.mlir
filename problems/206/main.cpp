#include <bits/stdc++.h>
using namespace std;
const int MX = 200005;
int len_[MX], link_[MX], to[MX][26], sz = 1, last = 1;
void ext(int c) {  // suffix automaton extension
    int cur = ++sz; len_[cur] = len_[last] + 1; int p = last;
    while (p && !to[p][c]) { to[p][c] = cur; p = link_[p]; }
    if (!p) link_[cur] = 1;
    else {
        int q = to[p][c];
        if (len_[q] == len_[p] + 1) link_[cur] = q;
        else {
            int cl = ++sz; len_[cl] = len_[p] + 1; link_[cl] = link_[q];
            memcpy(to[cl], to[q], sizeof(to[q]));
            while (p && to[p][c] == q) { to[p][c] = cl; p = link_[p]; }
            link_[q] = cl; link_[cur] = cl;
        }
    }
    last = cur;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s;
    for (char ch : s) ext(ch - 'a');
    int k; cin >> k;
    string out;
    while (k--) {
        string p; cin >> p; int u = 1; bool ok = true;
        for (char ch : p) { int c = ch - 'a'; if (!to[u][c]) { ok = false; break; } u = to[u][c]; }
        out += ok ? "YES\n" : "NO\n";
    }
    cout << out;
}
