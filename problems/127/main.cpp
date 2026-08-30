#include <bits/stdc++.h>
using namespace std;
int n;
int bit[200005];
void upd(int i, int d) { for (; i <= n; i += i & -i) bit[i] += d; }
int main() {
    scanf("%d", &n);
    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) { scanf("%d", &x[i]); upd(i, 1); }
    int LOG = 0;
    while ((1 << (LOG + 1)) <= n) LOG++;
    for (int i = 0; i < n; i++) {
        int p; scanf("%d", &p);
        // find the p-th still-alive position (smallest idx with prefix count == p)
        int pos = 0, sum = 0;
        for (int j = LOG; j >= 0; j--) {
            int np = pos + (1 << j);
            if (np <= n && sum + bit[np] < p) { pos = np; sum += bit[np]; }
        }
        pos++;
        printf("%d ", x[pos]);
        upd(pos, -1);
    }
    printf("\n");
}
