#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
string pr(__int128 v) { string o; if (v == 0) o = "0"; bool neg = v < 0; if (neg) v = -v; while (v) { o += ('0' + (int)(v % 10)); v /= 10; } if (neg) o += '-'; reverse(o.begin(), o.end()); return o; }
int main() {
    int n; scanf("%d", &n);
    vector<ll> x(n), y(n);
    for (int i = 0; i < n; i++) scanf("%lld %lld", &x[i], &y[i]);
    __int128 A2 = 0; long long B = 0;  // Pick: A = I + B/2 - 1
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        A2 += (__int128)x[i] * y[j] - (__int128)x[j] * y[i];
        B += __gcd(llabs(x[i] - x[j]), llabs(y[i] - y[j]));
    }
    if (A2 < 0) A2 = -A2;
    __int128 I = (A2 - B + 2) / 2;  // interior points
    printf("%s %lld\n", pr(I).c_str(), B);
}
