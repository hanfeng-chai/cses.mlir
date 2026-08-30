#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> p(n);
    long long total = 0;
    for (auto &x : p) { cin >> x; total += x; }
    long long best = LLONG_MAX;
    // 枚举每个子集作为第一组，最小化两组之差 |total - 2*subset|
    for (int mask = 0; mask < (1 << n); mask++) {
        long long s = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) s += p[i];
        best = min(best, llabs(total - 2 * s));
    }
    cout << best << '\n';
}
