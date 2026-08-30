#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    unordered_map<int, long long> cnt;
    cnt.reserve(2 * n);
    for (int i = 0; i < n; i++) { int x; cin >> x; cnt[x]++; }
    // 每个不同值：不选 或 选它的某一个出现 -> (出现次数+1) 种；任意位置子集都构成合法子序列
    long long ans = 1;
    for (auto &[v, c] : cnt) ans = ans * ((c + 1) % MOD) % MOD;
    ans = (ans - 1 + MOD) % MOD;  // 去掉空子序列
    cout << ans << '\n';
}
