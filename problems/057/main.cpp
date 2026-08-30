#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> x(n);
    long long lo = 0, hi = 0;
    for (auto &v : x) { cin >> v; lo = max(lo, v); hi += v; }
    // 二分最大子段和 mid，贪心分段，段数 <= k 即可行
    while (lo < hi) {
        long long mid = (lo + hi) / 2, cur = 0;
        int seg = 1;
        for (long long v : x) {
            if (cur + v > mid) { seg++; cur = v; }
            else cur += v;
        }
        if (seg <= k) hi = mid; else lo = mid + 1;
    }
    cout << lo << '\n';
}
