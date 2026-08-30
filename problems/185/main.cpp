#include <bits/stdc++.h>
using namespace std;
const int N = 10000001;
short twoA[N], twoB[N];
int main() {
    memset(twoA, -1, sizeof(twoA));
    for (int i = 0; (long long)i * i < N; i++)  // sieve: smallest rep of v as sum of two squares
        for (int j = i; (long long)i * i + (long long)j * j < N; j++) {
            int v = i * i + j * j;
            if (twoA[v] == -1) { twoA[v] = i; twoB[v] = j; }
        }
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int a = 0;; a++) {
            long long aa = (long long)a * a; if (aa > n) break;
            bool done = false;
            for (int b = a;; b++) {
                long long bb = (long long)b * b; if (aa + bb > n) break;
                int rem = n - aa - bb;
                if (twoA[rem] != -1) { printf("%d %d %d %d\n", a, b, (int)twoA[rem], (int)twoB[rem]); done = true; break; }
            }
            if (done) break;
        }
    }
}
