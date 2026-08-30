#include <bits/stdc++.h>
using namespace std;
int main() {
    int n; scanf("%d", &n);
    int B = 1; while ((1 << B) <= n) B++;  // bits needed to represent 1..n
    vector<int> a(n + 1, 0);
    string b(n, '0'), c;
    for (int t = 0; t < B; t++) {
        for (int j = 1; j <= n; j++) b[j - 1] = ((j >> t) & 1) ? '1' : '0';  // encode index j in bit t
        printf("? %s\n", b.c_str()); fflush(stdout);
        char buf[1005]; scanf("%s", buf); c = buf;
        for (int i = 1; i <= n; i++) if (c[i - 1] == '1') a[i] |= (1 << t);  // bit t of a_i
    }
    printf("!");
    for (int i = 1; i <= n; i++) printf(" %d", a[i]);
    printf("\n"); fflush(stdout);
}
