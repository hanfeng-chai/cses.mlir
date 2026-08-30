#include <bits/stdc++.h>
using namespace std;
const int MX = 200005;
int len_[MX], link_[MX], to[MX][26], sz = 1, last = 1, firstpos[MX];
long long cnt[MX];
void ext(int c, int pos) {
    int cur = ++sz; len_[cur] = len_[last] + 1; cnt[cur] = 1; firstpos[cur] = pos; int p = last;
    while (p && !to[p][c]) { to[p][c] = cur; p = link_[p]; }
    if (!p) link_[cur] = 1;
    else {
        int q = to[p][c];
        if (len_[q] == len_[p] + 1) link_[cur] = q;
        else {
            int cl = ++sz; len_[cl] = len_[p] + 1; link_[cl] = link_[q]; firstpos[cl] = firstpos[q]; cnt[cl] = 0;
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
    for (int i = 0; i < n; i++) ext(s[i] - 'a', i);
    vector<int> ord(sz + 1), bk(n + 2, 0);
    for (int v = 1; v <= sz; v++) bk[len_[v]]++;
    for (int i = 1; i <= n; i++) bk[i] += bk[i - 1];
    for (int v = 1; v <= sz; v++) ord[bk[len_[v]]--] = v;
    for (int i = sz; i >= 1; i--) { int v = ord[i]; if (link_[v]) cnt[link_[v]] += cnt[v]; }
    int bestlen = 0, bestv = -1;  // longest substring occurring >= 2 times
    for (int v = 2; v <= sz; v++) if (cnt[v] >= 2 && len_[v] > bestlen) { bestlen = len_[v]; bestv = v; }
    if (bestv == -1) { cout << -1 << "\n"; return 0; }
    int endi = firstpos[bestv];
    cout << s.substr(endi - bestlen + 1, bestlen) << "\n";
}
