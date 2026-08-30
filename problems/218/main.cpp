#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        long long x1, y1, x2, y2, x3, y3;
        scanf("%lld %lld %lld %lld %lld %lld", &x1, &y1, &x2, &y2, &x3, &y3);
        long long c = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);  // cross product sign
        puts(c > 0 ? "LEFT" : c < 0 ? "RIGHT" : "TOUCH");
    }
}
