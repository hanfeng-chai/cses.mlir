#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n, k; scanf("%lld %lld", &n, &k);
    vector<int> ans; ans.reserve(n);
    long long m = n;
    while (k > 0) {
        if (k >= m - 1) { ans.push_back((int)m); k -= m - 1; m--; }   // place the largest -> adds m-1 inversions
        else {
            ans.push_back((int)(k + 1));                              // adds exactly k inversions
            for (long long v = 1; v <= m; v++) if (v != k + 1) ans.push_back((int)v);
            m = 0; break;
        }
    }
    for (long long v = 1; v <= m; v++) ans.push_back((int)v);         // remaining values sorted
    string out; out.reserve(ans.size() * 7);
    for (int i = 0; i < (int)ans.size(); i++) { out += to_string(ans[i]); out += " \n"[i + 1 == (int)ans.size()]; }
    fwrite(out.data(), 1, out.size(), stdout);
}
