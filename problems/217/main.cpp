#include <bits/stdc++.h>
using namespace std;
const int MX = 200005;
int len_[MX], link_[MX], to[MX][26], sz = 1, last = 1;
void ext(int c) {
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
    string s; cin >> s; int n = s.size();
    for (char ch : s) ext(ch - 'a');
    // each state contributes one distinct substring for each length in (len[link], len]
    vector<long long> diff(n + 2, 0);
    for (int v = 2; v <= sz; v++) { diff[len_[link_[v]] + 1]++; diff[len_[v] + 1]--; }
    string out; long long cur = 0;
    for (int L = 1; L <= n; L++) { cur += diff[L]; out += to_string(cur); out += " \n"[L == n]; }
    cout << out;
}
