#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int LOG = 20, SZ = 1 << LOG;
ll f[SZ];
void fwht(ll *a) {
    for (int len = 1; len < SZ; len <<= 1)
        for (int i = 0; i < SZ; i += len << 1)
            for (int j = i; j < i + len; j++) { ll u = a[j], v = a[j + len]; a[j] = u + v; a[j + len] = u - v; }
}
int main() {
    int n; scanf("%d", &n);
    int px = 0; f[0]++;
    for (int i = 0; i < n; i++) { int x; scanf("%d", &x); px ^= x; f[px]++; }
    fwht(f);
    for (int i = 0; i < SZ; i++) f[i] *= f[i];
    fwht(f);
    for (int i = 0; i < SZ; i++) f[i] >>= LOG;  // f[v] = ordered pairs of prefix-xors with xor v
    vector<int> res;
    if (f[0] > (ll)(n + 1)) res.push_back(0);  // subarray xor 0 needs a repeated prefix-xor
    for (int v = 1; v < SZ; v++) if (f[v] > 0) res.push_back(v);
    printf("%d\n", (int)res.size());
    string out;
    for (int i = 0; i < (int)res.size(); i++) { out += to_string(res[i]); out += " \n"[i + 1 == (int)res.size()]; }
    cout << out;
}
