#include <bits/stdc++.h>
using namespace std;
int p[100005];
int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vector<array<long long, 3>> e(m);
    for (auto &E : e) {
        long long a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        E = {c, a, b};
    }
    sort(e.begin(), e.end());
    for (int i = 1; i <= n; i++) p[i] = i;
    long long cost = 0;
    int cnt = 0;
    for (auto &[c, a, b] : e)
        if (find(a) != find(b)) { p[find(a)] = find(b); cost += c; cnt++; }
    if (cnt != n - 1) printf("IMPOSSIBLE\n");
    else printf("%lld\n", cost);
}
