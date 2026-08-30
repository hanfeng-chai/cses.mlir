#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
struct P { ll x, y; bool operator<(const P &o) const { return x < o.x || (x == o.x && y < o.y); } bool operator==(const P &o) const { return x == o.x && y == o.y; } };
ll cross(const P &O, const P &A, const P &B) { return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x); }
bool onSeg(const P &a, const P &b, const P &q) {
    return min(a.x, b.x) <= q.x && q.x <= max(a.x, b.x) && min(a.y, b.y) <= q.y && q.y <= max(a.y, b.y);
}
// 2 boundary, 1 strictly inside, 0 outside
int onHull(vector<P> &V, const P &q) {
    int n = V.size();
    if (n == 1) return q == V[0] ? 2 : 0;
    if (n == 2) return (cross(V[0], V[1], q) == 0 && onSeg(V[0], V[1], q)) ? 2 : 0;
    ll c1 = cross(V[0], V[1], q), c2 = cross(V[0], V[n - 1], q);
    if (c1 < 0 || c2 > 0) return 0;
    if (c1 == 0) return onSeg(V[0], V[1], q) ? 2 : 0;
    if (c2 == 0) return onSeg(V[0], V[n - 1], q) ? 2 : 0;
    int lo = 1, hi = n - 1;
    while (hi - lo > 1) { int mid = (lo + hi) / 2; if (cross(V[0], V[mid], q) >= 0) lo = mid; else hi = mid; }
    ll c = cross(V[lo], V[lo + 1], q);
    if (c < 0) return 0;
    if (c == 0) return onSeg(V[lo], V[lo + 1], q) ? 2 : 0;
    return 1;
}
vector<P> strictHull(vector<P> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int m = p.size();
    vector<P> h(2 * m); int k = 0;
    for (int i = 0; i < m; i++) { while (k >= 2 && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--; h[k++] = p[i]; }
    for (int i = m - 2, t = k + 1; i >= 0; i--) { while (k >= t && cross(h[k - 2], h[k - 1], p[i]) <= 0) k--; h[k++] = p[i]; }
    h.resize(k - 1);
    return h;
}
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<P> pts(n);
    for (int i = 0; i < n; i++) { pts[i].x = inf.readLong(); pts[i].y = inf.readLong(); }
    vector<P> V = strictHull(pts);
    vector<P> truth;
    for (auto &q : pts) if (onHull(V, q) == 2) truth.push_back(q);
    sort(truth.begin(), truth.end());
    truth.erase(unique(truth.begin(), truth.end()), truth.end());
    int k = ouf.readInt();
    vector<P> got(k);
    for (int i = 0; i < k; i++) { got[i].x = ouf.readLong(); got[i].y = ouf.readLong(); }
    sort(got.begin(), got.end());
    int dup = unique(got.begin(), got.end()) - got.begin();
    if (dup != k) quitf(_wa, "duplicate points in output");
    if ((int)got.size() != (int)truth.size()) quitf(_wa, "got %d points, expected %d", (int)got.size(), (int)truth.size());
    for (int i = 0; i < (int)truth.size(); i++) if (!(got[i] == truth[i])) quitf(_wa, "point set mismatch");
    quitf(_ok, "%d hull points", (int)truth.size());
}
