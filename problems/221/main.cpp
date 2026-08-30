#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
    int n, m; scanf("%d %d", &n, &m);
    vector<ll> X(n), Y(n);
    for (int i = 0; i < n; i++) scanf("%lld %lld", &X[i], &Y[i]);
    while (m--) {
        ll px, py; scanf("%lld %lld", &px, &py);
        bool boundary = false, inside = false;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            ll xi = X[i], yi = Y[i], xj = X[j], yj = Y[j];
            ll cr = (xj - xi) * (py - yi) - (yj - yi) * (px - xi);
            if (cr == 0 && min(xi, xj) <= px && px <= max(xi, xj) && min(yi, yj) <= py && py <= max(yi, yj)) { boundary = true; break; }
            if ((yi > py) != (yj > py)) {  // ray-casting crossing test (integer)
                if ((cr > 0) == (yj > yi)) inside = !inside;
            }
        }
        puts(boundary ? "BOUNDARY" : inside ? "INSIDE" : "OUTSIDE");
    }
}
