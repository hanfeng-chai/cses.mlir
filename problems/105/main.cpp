#include <bits/stdc++.h>
using namespace std;
int p[100005], sz[100005];
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) { p[i] = i; sz[i] = 1; }
    int comp = n, mx = 1;
    while (m--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a = find(a); b = find(b);
        if (a != b) { p[a] = b; sz[b] += sz[a]; comp--; mx = max(mx, sz[b]); }
        printf("%d %d\n", comp, mx);
    }
}
