#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct P { ll x, y; bool operator<(const P &o) const { return x < o.x || (x == o.x && y < o.y); } bool operator==(const P &o) const { return x == o.x && y == o.y; } };
ll cross(const P &O, const P &A, const P &B) { return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x); }
int main() {
    int n; scanf("%d", &n);
    vector<P> p(n);
    for (auto &q : p) scanf("%lld %lld", &q.x, &q.y);
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int m = p.size();
    vector<P> h;  // collinear-keeping monotone chain (cross < 0 keeps boundary-collinear points)
    for (int i = 0; i < m; i++) { while (h.size() >= 2 && cross(h[h.size() - 2], h[h.size() - 1], p[i]) < 0) h.pop_back(); h.push_back(p[i]); }
    int lower = h.size() + 1;
    for (int i = m - 2; i >= 0; i--) { while ((int)h.size() >= lower && cross(h[h.size() - 2], h[h.size() - 1], p[i]) < 0) h.pop_back(); h.push_back(p[i]); }
    h.pop_back();
    sort(h.begin(), h.end());
    h.erase(unique(h.begin(), h.end()), h.end());
    printf("%d\n", (int)h.size());
    for (auto &q : h) printf("%lld %lld\n", q.x, q.y);
}
