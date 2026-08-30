#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; scanf("%d", &t);
    string out;
    while (t--) {
        long long n, k; scanf("%lld %lld", &n, &k);
        if (k * k < n) { out += "IMPOSSIBLE\n"; continue; }
        long long b = (n + k - 1) / k;  // number of blocks (= longest decreasing)
        vector<long long> sizes(b);
        for (long long i = 0; i < b - 1; i++) sizes[i] = k;
        sizes[b - 1] = n - (b - 1) * k;
        long long prefix = 0;  // each block increasing, blocks decreasing in value
        for (long long i = 0; i < b; i++) {
            long long high = n - prefix, low = high - sizes[i] + 1;
            for (long long v = low; v <= high; v++) { out += to_string(v); out += ' '; }
            prefix += sizes[i];
        }
        out.back() = '\n';
    }
    cout << out;
}
