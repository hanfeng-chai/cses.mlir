#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    vector<long long> p(n);
    for (auto &v : p) cin >> v;
    sort(p.begin(), p.end());
    int lo = 0, hi = n - 1, g = 0;
    // 最重的人尽量和最轻的人拼一个吊舱
    while (lo <= hi) {
        if (p[lo] + p[hi] <= x) lo++;  // 最轻者也能拼上
        hi--;                          // 最重者就坐
        g++;
    }
    cout << g << '\n';
}
