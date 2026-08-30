#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MX = 200005;
int lc[MX], rc[MX], sz[MX], cnt = 0; bool rev[MX];
unsigned pri[MX]; ll val[MX], sum[MX];
mt19937 rng(998244353);
int newnode(ll c) { int x = ++cnt; lc[x] = rc[x] = 0; sz[x] = 1; pri[x] = rng(); val[x] = sum[x] = c; rev[x] = false; return x; }
void upd(int x) { if (x) { sz[x] = 1 + sz[lc[x]] + sz[rc[x]]; sum[x] = val[x] + sum[lc[x]] + sum[rc[x]]; } }
void push(int x) { if (rev[x]) { swap(lc[x], rc[x]); if (lc[x]) rev[lc[x]] ^= 1; if (rc[x]) rev[rc[x]] ^= 1; rev[x] = false; } }
void split(int t, int k, int &a, int &b) {
    if (!t) { a = b = 0; return; }
    push(t);
    if (sz[lc[t]] >= k) { split(lc[t], k, a, lc[t]); b = t; }
    else { split(rc[t], k - sz[lc[t]] - 1, rc[t], b); a = t; }
    upd(t);
}
int merge(int a, int b) {
    if (!a || !b) return a | b;
    if (pri[a] < pri[b]) { push(a); rc[a] = merge(rc[a], b); upd(a); return a; }
    else { push(b); lc[b] = merge(a, lc[b]); upd(b); return b; }
}
int main() {
    int n, m; scanf("%d %d", &n, &m);
    int root = 0;
    for (int i = 0; i < n; i++) { ll v; scanf("%lld", &v); root = merge(root, newnode(v)); }
    string out;
    while (m--) {
        int t, a, b; scanf("%d %d %d", &t, &a, &b);
        int L, M, R;
        split(root, b, L, R);
        split(L, a - 1, L, M);  // M = a..b
        if (t == 1) rev[M] ^= 1;
        else { out += to_string(sum[M]); out += '\n'; }
        root = merge(merge(L, M), R);
    }
    cout << out;
}
