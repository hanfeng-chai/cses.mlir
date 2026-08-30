#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k; scanf("%d %d", &n, &k);
    vector<int> b(n);
    for (auto &v : b) scanf("%d", &v);
    int d = n - k, len = n;
    for (int t = 0; (1 << t) <= d; t++)  // applying the xor step 2^t times = b[j] ^= b[j+2^t]
        if (d >> t & 1) { int s = 1 << t; for (int j = 0; j + s < len; j++) b[j] ^= b[j + s]; len -= s; }
    string out;
    for (int j = 0; j < k; j++) { out += to_string(b[j]); out += " \n"[j == k - 1]; }
    cout << out;
}
