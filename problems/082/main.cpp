#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;
int n;
long long bit[200005];
void upd(int i, long long v) { for (; i <= n; i += i & -i) bit[i] = (bit[i] + v) % MOD; }
long long qry(int i) { long long s = 0; for (; i > 0; i -= i & -i) s = (s + bit[i]) % MOD; return s; }
int main() {
    cin >> n;
    vector<int> x(n);
    for (auto &v : x) cin >> v;
    vector<int> srt(x);
    sort(srt.begin(), srt.end());
    srt.erase(unique(srt.begin(), srt.end()), srt.end());
    auto idx = [&](int v) { return int(lower_bound(srt.begin(), srt.end(), v) - srt.begin()) + 1; };
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int r = idx(x[i]);
        long long cnt = (qry(r - 1) + 1) % MOD;  // self + all ending with a strictly smaller value
        upd(r, cnt);
        ans = (ans + cnt) % MOD;
    }
    cout << ans % MOD << "\n";
}
