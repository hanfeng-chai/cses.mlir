#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> v(n);  // (时长, 截止)
    for (auto &[a, d] : v) cin >> a >> d;
    sort(v.begin(), v.end());  // 按时长升序，最小化总完成时间
    long long t = 0, ans = 0;
    for (auto &[a, d] : v) { t += a; ans += d - t; }
    cout << ans << '\n';
}
