#include <bits/stdc++.h>
using namespace std;
// cost(a,b) = sum_{i=a..b}(prefMax_i - x_i). Offline, sweep a from n down to 1
// maintaining prefMax per position with a monotonic stack + range-add/range-sum BIT.
int n, q;
long long b1[200005], b2[200005];
void add(long long *b, int i, long long d) { for (; i <= n; i += i & -i) b[i] += d; }
long long sum(long long *b, int i) { long long s = 0; for (; i > 0; i -= i & -i) s += b[i]; return s; }
void rangeAdd(int l, int r, long long d) { add(b1, l, d); add(b1, r + 1, -d); add(b2, l, d * (l - 1)); add(b2, r + 1, -d * r); }
long long prefix(int i) { return sum(b1, i) * i - sum(b2, i); }
long long rangeSum(int l, int r) { return prefix(r) - prefix(l - 1); }
int main() {
    scanf("%d %d", &n, &q);
    vector<long long> x(n + 1), px(n + 1, 0);
    for (int i = 1; i <= n; i++) { scanf("%lld", &x[i]); px[i] = px[i - 1] + x[i]; }
    vector<array<int, 3>> qs(q);
    for (int i = 0; i < q; i++) { int a, b; scanf("%d %d", &a, &b); qs[i] = {a, b, i}; }
    sort(qs.begin(), qs.end(), [](auto &A, auto &B) { return A[0] > B[0]; });  // a descending
    vector<long long> ans(q);
    vector<array<long long, 3>> st;  // (value, left, right) segments of equal prefMax
    int qi = 0;
    for (int a = n; a >= 1; a--) {
        long long xv = x[a];
        int curR = a;
        while (!st.empty() && st.back()[0] <= xv) {
            auto sg = st.back(); st.pop_back();
            rangeAdd((int)sg[1], (int)sg[2], xv - sg[0]);
            curR = (int)sg[2];
        }
        rangeAdd(a, a, xv);
        st.push_back({xv, (long long)a, (long long)curR});
        while (qi < q && qs[qi][0] == a) {
            int b = qs[qi][1], id = qs[qi][2];
            ans[id] = rangeSum(a, b) - (px[b] - px[a - 1]);
            qi++;
        }
    }
    for (int i = 0; i < q; i++) printf("%lld\n", ans[i]);
}
