#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
__int128 sumAbs(vector<ll> a) {  // sum of |a_i - a_j| over all pairs
    sort(a.begin(), a.end());
    ll pre = 0; __int128 res = 0;
    for (int i = 0; i < (int)a.size(); i++) { res += (__int128)((ll)a[i] * i) - pre; pre += a[i]; }
    return res;
}
int main() {
    int n; scanf("%d", &n);
    vector<ll> X(n), Y(n);
    for (int i = 0; i < n; i++) scanf("%lld %lld", &X[i], &Y[i]);
    __int128 ans = sumAbs(X) + sumAbs(Y);
    string out; if (ans == 0) out = "0";
    while (ans) { out += ('0' + (int)(ans % 10)); ans /= 10; }
    reverse(out.begin(), out.end());
    printf("%s\n", out.c_str());
}
