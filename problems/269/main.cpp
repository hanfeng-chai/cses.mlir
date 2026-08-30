#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG = -4e18;
int M;
struct Line { ll m, b; ll val(ll x) { return m * x + b; } };
vector<Line> seg;
void insert(int node, int lo, int hi, Line ln) {  // Li Chao max
    int mid = (lo + hi) / 2;
    bool l = ln.val(lo) > seg[node].val(lo);
    bool md = ln.val(mid) > seg[node].val(mid);
    if (md) swap(seg[node], ln);
    if (lo == hi) return;
    if (l != md) insert(2 * node, lo, mid, ln);
    else insert(2 * node + 1, mid + 1, hi, ln);
}
void insertSeg(int node, int lo, int hi, int ql, int qr, Line ln) {
    if (qr < lo || hi < ql) return;
    if (ql <= lo && hi <= qr) { insert(node, lo, hi, ln); return; }
    int mid = (lo + hi) / 2; insertSeg(2 * node, lo, mid, ql, qr, ln); insertSeg(2 * node + 1, mid + 1, hi, ql, qr, ln);
}
ll query(int node, int lo, int hi, int x) {
    ll r = seg[node].val(x);
    if (lo == hi) return r;
    int mid = (lo + hi) / 2;
    if (x <= mid) return max(r, query(2 * node, lo, mid, x));
    return max(r, query(2 * node + 1, mid + 1, hi, x));
}
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<ll> h(n);
    for (auto &v : h) scanf("%lld", &v);
    vector<int> L(n), R(n), st;
    for (int i = 0; i < n; i++) { while (!st.empty() && h[st.back()] >= h[i]) st.pop_back(); L[i] = st.empty() ? -1 : st.back(); st.push_back(i); }
    st.clear();
    for (int i = n - 1; i >= 0; i--) { while (!st.empty() && h[st.back()] >= h[i]) st.pop_back(); R[i] = st.empty() ? n : st.back(); st.push_back(i); }
    M = n - k;
    seg.assign(4 * (M + 1), Line{0, NEG});
    auto addLine = [&](int lo, int hi, ll slope, ll inter) {
        lo = max(lo, 0); hi = min(hi, M);
        if (lo > hi) return;
        insertSeg(1, 0, M, lo, hi, Line{slope, inter});
    };
    for (int i = 0; i < n; i++) {
        ll hi_ = h[i];
        int A = L[i] + 1, B = R[i] - 1;            // span [A,B]: all bars >= h[i], bar i is a minimum
        int Wlo = max(0, i - k + 1), Whi = min(i, M);
        if (Wlo > Whi) continue;
        int p2 = B - k + 1;
        if (A <= p2) {  // span at least as wide as the window
            addLine(Wlo, A - 1, hi_, hi_ * (k - A));            // window entering: width = w + (k - A)
            addLine(A, p2, 0, hi_ * (ll)k);                    // window fully inside span: width = k
            addLine(p2 + 1, Whi, -hi_, hi_ * (ll)(B + 1));     // window leaving: width = (B + 1) - w
        } else {        // span narrower than the window
            addLine(Wlo, p2, hi_, hi_ * (k - A));
            addLine(p2 + 1, A - 1, 0, hi_ * (ll)(B - A + 1));  // span fully inside window: width = B - A + 1
            addLine(A, Whi, -hi_, hi_ * (ll)(B + 1));
        }
    }
    string out;
    for (int w = 0; w <= M; w++) { out += to_string(query(1, 0, M, w)); out += " \n"[w == M]; }
    cout << out;
}
