#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    long long maxU = LLONG_MIN, minU = LLONG_MAX, maxV = LLONG_MIN, minV = LLONG_MAX;
    string out;
    for (int i = 0; i < n; i++) {
        long long x, y; scanf("%lld %lld", &x, &y);
        long long u = x + y, v = x - y;  // Manhattan = max(|du|, |dv|) under rotation
        maxU = max(maxU, u); minU = min(minU, u); maxV = max(maxV, v); minV = min(minV, v);
        out += to_string(max(maxU - minU, maxV - minV)); out += '\n';
    }
    cout << out;
}
