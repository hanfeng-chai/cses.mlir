#include <bits/stdc++.h>
using namespace std;
const int MX = 200005;
int len_[MX], link_[MX], to[MX][26], sz = 1, last = 1;
long long cnt[MX];
void ext(int c) {
    int cur = ++sz; len_[cur] = len_[last] + 1; cnt[cur] = 1; int p = last;
    while (p && !to[p][c]) { to[p][c] = cur; p = link_[p]; }
    if (!p) link_[cur] = 1;
    else {
        int q = to[p][c];
        if (len_[q] == len_[p] + 1) link_[cur] = q;
        else {
            int cl = ++sz; len_[cl] = len_[p] + 1; link_[cl] = link_[q]; cnt[cl] = 0;
            memcpy(to[cl], to[q], sizeof(to[q]));
            while (p && to[p][c] == q) { to[p][c] = cl; p = link_[p]; }
            link_[q] = cl; link_[cur] = cl;
        }
    }
    last = cur;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string s; cin >> s; int n = s.size();
    for (char ch : s) ext(ch - 'a');
    // propagate endpos sizes in order of decreasing len (counting sort)
    vector<int> ord(sz + 1), bucket(n + 2, 0);
    for (int v = 1; v <= sz; v++) bucket[len_[v]]++;
    for (int i = 1; i <= n; i++) bucket[i] += bucket[i - 1];
    for (int v = 1; v <= sz; v++) ord[bucket[len_[v]]--] = v;
    for (int i = sz; i >= 1; i--) { int v = ord[i]; if (link_[v]) cnt[link_[v]] += cnt[v]; }
    int k; cin >> k;
    string out;
    while (k--) {
        string p; cin >> p; int u = 1; bool ok = true;
        for (char ch : p) { int c = ch - 'a'; if (!to[u][c]) { ok = false; break; } u = to[u][c]; }
        out += ok ? to_string(cnt[u]) : "0"; out += '\n';
    }
    cout << out;
}
