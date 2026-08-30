#include <bits/stdc++.h>
using namespace std;

int n, M;
vector<int> bit;
void upd(int i) { for (; i <= M; i += i & -i) bit[i]++; }
int qry(int i) { int s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    vector<array<int, 3>> v(n);
    vector<int> ys(n);
    for (int i = 0; i < n; i++) { cin >> v[i][0] >> v[i][1]; v[i][2] = i; ys[i] = v[i][1]; }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    M = ys.size();
    auto cy = [&](int y) { return int(lower_bound(ys.begin(), ys.end(), y) - ys.begin()) + 1; };
    sort(v.begin(), v.end(), [](auto &a, auto &b) {
        return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
    });
    vector<int> contained(n), contains(n);
    // 被包含数：前面(x'<=x)中 y'>=y 的个数
    bit.assign(M + 1, 0);
    for (int i = 0; i < n; i++) {
        int yi = cy(v[i][1]);
        contained[v[i][2]] = i - qry(yi - 1);
        upd(yi);
    }
    // 包含他人数：后面(x'>=x)中 y'<=y 的个数
    bit.assign(M + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        int yi = cy(v[i][1]);
        contains[v[i][2]] = qry(yi);
        upd(yi);
    }
    for (int i = 0; i < n; i++) cout << contains[i] << " \n"[i == n - 1];
    for (int i = 0; i < n; i++) cout << contained[i] << " \n"[i == n - 1];
}
