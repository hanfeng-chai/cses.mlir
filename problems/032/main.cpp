#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    long long best = LLONG_MIN, cur = 0;
    // Kadane：cur 累加，遇负归零；best 记录全程最大（含全负情形）
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        cur += x;
        best = max(best, cur);
        if (cur < 0) cur = 0;
    }
    cout << best << '\n';
}
