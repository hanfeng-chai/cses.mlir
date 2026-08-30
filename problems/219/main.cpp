#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll cross(ll ox, ll oy, ll ax, ll ay, ll bx, ll by) { return (ax - ox) * (by - oy) - (ay - oy) * (bx - ox); }
int sgn(ll x) { return (x > 0) - (x < 0); }
bool onSeg(ll px, ll py, ll qx, ll qy, ll rx, ll ry) {  // r on segment pq (collinear assumed)
    return min(px, qx) <= rx && rx <= max(px, qx) && min(py, qy) <= ry && ry <= max(py, qy);
}
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        ll x1, y1, x2, y2, x3, y3, x4, y4;
        scanf("%lld %lld %lld %lld %lld %lld %lld %lld", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
        int d1 = sgn(cross(x3, y3, x4, y4, x1, y1)), d2 = sgn(cross(x3, y3, x4, y4, x2, y2));
        int d3 = sgn(cross(x1, y1, x2, y2, x3, y3)), d4 = sgn(cross(x1, y1, x2, y2, x4, y4));
        bool inter = false;
        if (d1 != d2 && d3 != d4) inter = true;
        else if (d1 == 0 && onSeg(x3, y3, x4, y4, x1, y1)) inter = true;
        else if (d2 == 0 && onSeg(x3, y3, x4, y4, x2, y2)) inter = true;
        else if (d3 == 0 && onSeg(x1, y1, x2, y2, x3, y3)) inter = true;
        else if (d4 == 0 && onSeg(x1, y1, x2, y2, x4, y4)) inter = true;
        puts(inter ? "YES" : "NO");
    }
}
