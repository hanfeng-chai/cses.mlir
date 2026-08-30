#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> a(n);
    for (auto &v : a) cin >> v;
    // 正数数组：双指针维护和 <= x 的窗口
    long long sum = 0, cnt = 0;
    int l = 0;
    for (int r = 0; r < n; r++) {
        sum += a[r];
        while (sum > x) sum -= a[l++];
        if (sum == x) cnt++;
    }
    cout << cnt << '\n';
}
