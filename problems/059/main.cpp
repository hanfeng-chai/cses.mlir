#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b;
    cin >> n >> a >> b;
    vector<long long> P(n + 1, 0);
    for (int i = 1; i <= n; i++) { long long x; cin >> x; P[i] = P[i - 1] + x; }
    // 子数组 (l,r] 和 = P[r]-P[l]，长度 r-l ∈ [a,b]，即 l ∈ [r-b, r-a]
    // 单调队列维护窗口内最小 P[l]
    deque<int> dq;
    long long ans = LLONG_MIN;
    for (int r = a; r <= n; r++) {
        int l = r - a;  // 新进入窗口的左端前缀下标
        while (!dq.empty() && P[dq.back()] >= P[l]) dq.pop_back();
        dq.push_back(l);
        while (dq.front() < r - b) dq.pop_front();  // 移除越界的
        ans = max(ans, P[r] - P[dq.front()]);
    }
    cout << ans << '\n';
}
