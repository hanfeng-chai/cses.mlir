#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        bool odd = false;
        for (int i = 0; i < n; i++) { int v; scanf("%d", &v); if (v & 1) odd = true; }
        // all-even is a P-position; any odd heap lets first move to all-even
        puts(odd ? "first" : "second");
    }
}
