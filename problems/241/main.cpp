#include <bits/stdc++.h>
using namespace std;
const int MX = 200005;
int lc[MX], rc[MX], sz[MX], cnt = 0; bool rev[MX];
unsigned pri[MX]; char val[MX];
mt19937 rng(998244353);
int newnode(char c) { int x = ++cnt; lc[x] = rc[x] = 0; sz[x] = 1; pri[x] = rng(); val[x] = c; rev[x] = false; return x; }
void upd(int x) { if (x) sz[x] = 1 + sz[lc[x]] + sz[rc[x]]; }
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
void output(int t, string &s) { if (!t) return; push(t); output(lc[t], s); s += val[t]; output(rc[t], s); }
int main() {
    int n, m; scanf("%d %d", &n, &m);
    static char buf[MX]; scanf("%s", buf);
    int root = 0;
    for (int i = 0; i < n; i++) root = merge(root, newnode(buf[i]));
    while (m--) {
        int a, b; scanf("%d %d", &a, &b);
        int L, M, R;
        split(root, b, L, R);
        split(L, a - 1, L, M);
        rev[M] ^= 1;  // lazily reverse the middle part
        root = merge(merge(L, M), R);
    }
    string s; output(root, s);
    printf("%s\n", s.c_str());
}
