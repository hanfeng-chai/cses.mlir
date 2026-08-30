#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, t;
    cin >> n >> t;
    vector<long long> k(n);
    long long mn = LLONG_MAX;
    for (auto &v : k) { cin >> v; mn = min(mn, v); }
    // 二分时间：T 秒内能造 sum(T/k_i) 个产品，求满足 >= t 的最小 T
    long long lo = 1, hi = mn * t;
    while (lo < hi) {
        long long mid = (lo + hi) / 2, cnt = 0;
        for (long long ki : k) {
            cnt += mid / ki;
            if (cnt >= t) break;
        }
        if (cnt >= t) hi = mid; else lo = mid + 1;
    }
    cout << lo << '\n';
}
