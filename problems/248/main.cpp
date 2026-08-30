#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;
struct CHT {  // min, slopes added decreasing, queries increasing
    vector<ll> M, B; int head = 0;
    bool bad(int a, int b, int c) { return (__int128)(B[c] - B[a]) * (M[a] - M[b]) <= (__int128)(B[b] - B[a]) * (M[a] - M[c]); }
    void add(ll m, ll b) {
        M.push_back(m); B.push_back(b); int n = M.size();
        while (n >= 3 && bad(n - 3, n - 2, n - 1)) { M[n - 2] = M[n - 1]; B[n - 2] = B[n - 1]; M.pop_back(); B.pop_back(); n--; }
        if (head >= (int)M.size()) head = M.size() - 1;
    }
    ll query(ll x) {
        if (head >= (int)M.size()) head = M.size() - 1;
        while (head + 1 < (int)M.size() && M[head + 1] * x + B[head + 1] <= M[head] * x + B[head]) head++;
        return M[head] * x + B[head];
    }
};
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<ll> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) { ll v; scanf("%lld", &v); pre[i] = pre[i - 1] + v; }
    vector<ll> dpPrev(n + 1, INF), dpCur(n + 1, INF);
    dpPrev[0] = 0;
    for (int j = 1; j <= k; j++) {
        CHT cht;
        for (int i = 1; i <= n; i++) {
            int p = i - 1;
            if (dpPrev[p] < INF) cht.add(-2 * pre[p], dpPrev[p] + pre[p] * pre[p]);
            dpCur[i] = cht.M.empty() ? INF : cht.query(pre[i]) + pre[i] * pre[i];
        }
        dpCur[0] = INF;
        swap(dpPrev, dpCur);
    }
    printf("%lld\n", dpPrev[n]);
}
