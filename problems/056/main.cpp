#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (auto &v : x) cin >> v;
    // 滑动窗口：维护至多 k 种不同值的窗口，累加每个右端的合法子数组数
    unordered_map<int, int> cnt;
    cnt.reserve(2 * n);
    int distinct = 0, l = 0;
    long long ans = 0;
    for (int r = 0; r < n; r++) {
        if (cnt[x[r]]++ == 0) distinct++;
        while (distinct > k) {
            if (--cnt[x[l]] == 0) distinct--;
            l++;
        }
        ans += r - l + 1;
    }
    cout << ans << '\n';
}
