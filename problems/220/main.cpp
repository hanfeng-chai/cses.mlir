#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; i++) scanf("%lld %lld", &x[i], &y[i]);
    __int128 s = 0;  // shoelace; output 2a = |s|
    for (int i = 0; i < n; i++) { int j = (i + 1) % n; s += (__int128)x[i] * y[j] - (__int128)x[j] * y[i]; }
    if (s < 0) s = -s;
    string out;
    if (s == 0) out = "0";
    while (s) { out += ('0' + (int)(s % 10)); s /= 10; }
    reverse(out.begin(), out.end());
    printf("%s\n", out.c_str());
}
