#include <bits/stdc++.h>
using namespace std;
const int MX = 200005;
int lc[MX], rc[MX], sz[MX], cnt = 0;
unsigned pri[MX]; char val[MX];
mt19937 rng(998244353);
int newnode(char c) { int x = ++cnt; lc[x] = rc[x] = 0; sz[x] = 1; pri[x] = rng(); val[x] = c; return x; }
void upd(int x) { if (x) sz[x] = 1 + sz[lc[x]] + sz[rc[x]]; }
void split(int t, int k, int &a, int &b) {  // first k nodes to a
    if (!t) { a = b = 0; return; }
    if (sz[lc[t]] >= k) { split(lc[t], k, a, lc[t]); b = t; }
    else { split(rc[t], k - sz[lc[t]] - 1, rc[t], b); a = t; }
    upd(t);
}
int merge(int a, int b) {
    if (!a || !b) return a | b;
    if (pri[a] < pri[b]) { rc[a] = merge(rc[a], b); upd(a); return a; }
    else { lc[b] = merge(a, lc[b]); upd(b); return b; }
}
void output(int t, string &s) { if (!t) return; output(lc[t], s); s += val[t]; output(rc[t], s); }
int main() {
    int n, m; scanf("%d %d", &n, &m);
    static char buf[MX]; scanf("%s", buf);
    int root = 0;
    for (int i = 0; i < n; i++) root = merge(root, newnode(buf[i]));
    while (m--) {
        int a, b; scanf("%d %d", &a, &b);
        int L, M, R;
        split(root, b, L, R);       // L = 1..b
        split(L, a - 1, L, M);      // M = a..b
        root = merge(merge(L, R), M);  // paste cut piece to the end
    }
    string s; output(root, s);
    printf("%s\n", s.c_str());
}
