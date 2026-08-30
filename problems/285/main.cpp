#include <bits/stdc++.h>
using namespace std;
const int LOG = 20, M = 1 << LOG;
int sub[M], sup[M];
int main() {
    int n; scanf("%d", &n);
    vector<int> x(n);
    for (int i = 0; i < n; i++) { scanf("%d", &x[i]); sub[x[i]]++; sup[x[i]]++; }
    for (int b = 0; b < LOG; b++) for (int m = 0; m < M; m++) if (m >> b & 1) sub[m] += sub[m ^ (1 << b)];        // submask sum
    for (int b = 0; b < LOG; b++) for (int m = 0; m < M; m++) if (!(m >> b & 1)) sup[m] += sup[m | (1 << b)];     // supermask sum
    string out;
    for (int i = 0; i < n; i++) {
        int comp = (~x[i]) & (M - 1);
        // 1) x|y==x -> y submask of x ; 2) x&y==x -> y supermask of x ; 3) x&y!=0 -> n - (y disjoint from x)
        out += to_string(sub[x[i]]); out += ' ';
        out += to_string(sup[x[i]]); out += ' ';
        out += to_string(n - sub[comp]); out += '\n';
    }
    cout << out;
}
