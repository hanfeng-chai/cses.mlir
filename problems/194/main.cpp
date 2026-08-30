#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        int x = 0;
        for (int i = 1; i <= n; i++) { int v; scanf("%d", &v); if (i % 2 == 0) x ^= v; }  // staircase Nim: even-indexed stairs
        puts(x ? "first" : "second");
    }
}
