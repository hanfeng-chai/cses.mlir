#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> x(n);
    for (auto &v : x) cin >> v;
    sort(x.begin(), x.end());
    long long reach = 0;  // 当前可凑出 [1, reach]
    for (long long c : x) {
        if (c > reach + 1) break;  // reach+1 无法凑出
        reach += c;
    }
    cout << reach + 1 << '\n';
}
