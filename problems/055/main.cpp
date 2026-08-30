#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    // 前缀和模 n 相等的两端点构成可被 n 整除的子数组
    vector<long long> cnt(n, 0);
    cnt[0] = 1;
    long long pre = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        pre = ((pre + a) % n + n) % n;
        ans += cnt[pre];
        cnt[pre]++;
    }
    cout << ans << '\n';
}
