#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, k;
map<int, ll> cf, cs;
const ll INF = 2e9;
ll getF(int i) {  // i-th highest Finland; out of range -> +inf above, -inf below
    if (i < 1) return INF;
    if (i > n) return -INF;
    auto it = cf.find(i); if (it != cf.end()) return it->second;
    printf("F %d\n", i); fflush(stdout); ll v; scanf("%lld", &v); cf[i] = v; return v;
}
ll getS(int i) {
    if (i < 1) return INF;
    if (i > n) return -INF;
    auto it = cs.find(i); if (it != cs.end()) return it->second;
    printf("S %d\n", i); fflush(stdout); ll v; scanf("%lld", &v); cs[i] = v; return v;
}
int main() {
    scanf("%d %d", &n, &k);
    // find max i (Finland count among top k) with getF(i) >= getS(k-i+1)
    int lo = max(0, k - n), hi = min(k, n);
    while (lo < hi) {
        int i = (lo + hi + 1) / 2;
        if (getF(i) >= getS(k - i + 1)) lo = i; else hi = i - 1;
    }
    int i = lo;
    ll ans = min(getF(i), getS(k - i));  // k-th highest = smallest of the chosen top k
    printf("! %lld\n", ans); fflush(stdout);
}
