#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<array<int, 3>> v(n);  // x, y, 原始下标
    for (int i = 0; i < n; i++) { cin >> v[i][0] >> v[i][1]; v[i][2] = i; }
    // x 升序、y 降序：同 x 时更长的区间排前面
    sort(v.begin(), v.end(), [](auto &a, auto &b) {
        return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
    });
    vector<int> contained(n), contains(n);
    int maxY = -1;  // 被包含：前面存在 x'<=x 且 y'>=y
    for (int i = 0; i < n; i++) {
        contained[v[i][2]] = (maxY >= v[i][1]) ? 1 : 0;
        maxY = max(maxY, v[i][1]);
    }
    int minY = INT_MAX;  // 包含他人：后面（x'>=x）存在 y'<=y
    for (int i = n - 1; i >= 0; i--) {
        contains[v[i][2]] = (minY <= v[i][1]) ? 1 : 0;
        minY = min(minY, v[i][1]);
    }
    for (int i = 0; i < n; i++) cout << contains[i] << " \n"[i == n - 1];
    for (int i = 0; i < n; i++) cout << contained[i] << " \n"[i == n - 1];
}
