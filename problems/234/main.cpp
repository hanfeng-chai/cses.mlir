#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; long long x; scanf("%d %lld", &n, &x);
    vector<long long> t(n);
    for (auto &v : t) scanf("%lld", &v);
    int h1 = n / 2, h2 = n - h1;
    vector<long long> s1, s2;
    for (int m = 0; m < (1 << h1); m++) { long long s = 0; for (int i = 0; i < h1; i++) if (m >> i & 1) s += t[i]; s1.push_back(s); }
    for (int m = 0; m < (1 << h2); m++) { long long s = 0; for (int i = 0; i < h2; i++) if (m >> i & 1) s += t[h1 + i]; s2.push_back(s); }
    sort(s2.begin(), s2.end());
    long long cnt = 0;
    for (long long s : s1) {
        long long need = x - s;
        cnt += upper_bound(s2.begin(), s2.end(), need) - lower_bound(s2.begin(), s2.end(), need);
    }
    printf("%lld\n", cnt);
}
