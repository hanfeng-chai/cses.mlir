#include <bits/stdc++.h>
using namespace std;
int d[1000001];
int main() {
    for (int i = 1; i <= 1000000; i++)
        for (int j = i; j <= 1000000; j += i) d[j]++;
    int n; scanf("%d", &n);
    while (n--) { int x; scanf("%d", &x); printf("%d\n", d[x]); }
}
