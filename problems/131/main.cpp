#include <bits/stdc++.h>
using namespace std;
// Building i is visible in [a,b] iff the nearest j<i with h[j]>=h[i] is < a.
// Offline: count i in [a,b] with L[i] < a, activating positions by increasing L.
int n, q;
int bit[100005];
void upd(int i, int d) { for (; i <= n; i += i & -i) bit[i] += d; }
int qsum(int i) { int s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
int main() {
    scanf("%d %d", &n, &q);
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    vector<int> L(n + 1);
    vector<int> st;  // decreasing-height stack of indices
    for (int i = 1; i <= n; i++) {
        while (!st.empty() && h[st.back()] < h[i]) st.pop_back();
        L[i] = st.empty() ? 0 : st.back();
        st.push_back(i);
    }
    vector<vector<int>> byL(n + 1);
    for (int i = 1; i <= n; i++) byL[L[i]].push_back(i);
    vector<array<int, 3>> queries(q);  // a, b, original index
    for (int i = 0; i < q; i++) { int a, b; scanf("%d %d", &a, &b); queries[i] = {a, b, i}; }
    sort(queries.begin(), queries.end());  // by a ascending
    vector<int> ans(q);
    int curL = 0;  // all positions with L < a must be activated
    for (auto &qq : queries) {
        int a = qq[0], b = qq[1], id = qq[2];
        while (curL < a) { for (int i : byL[curL]) upd(i, 1); curL++; }
        ans[id] = qsum(b) - qsum(a - 1);
    }
    for (int i = 0; i < q; i++) printf("%d\n", ans[i]);
}
