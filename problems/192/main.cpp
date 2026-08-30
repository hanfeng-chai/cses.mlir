#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        int x = 0;
        for (int i = 0; i < n; i++) { int v; scanf("%d", &v); x ^= v; }
        puts(x ? "first" : "second");  // standard Nim
    }
}
