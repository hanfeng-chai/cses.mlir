#include <bits/stdc++.h>
using namespace std;
int n;
int ask(int i) { printf("? %d\n", i); fflush(stdout); char buf[4]; scanf("%s", buf); return buf[0] == 'R' ? 0 : 1; }
int main() {
    scanf("%d", &n);
    int c1 = ask(1), cn = ask(n);
    if (cn == c1) { printf("! %d\n", n); fflush(stdout); return 0; }  // chairs n and 1 share color
    // m(i) = color[i] != expected(i); expected(i) = c1 XOR ((i-1)&1). m flips where a same-color pair sits.
    int lo = 1, hi = n;  // m(lo)=0, m(hi)=1
    while (hi - lo > 1) {
        int mid = (lo + hi) / 2;
        int cm = ask(mid);
        int mm = (cm != (c1 ^ ((mid - 1) & 1)));
        if (mm == 0) lo = mid; else hi = mid;
    }
    printf("! %d\n", lo); fflush(stdout);  // chairs lo and lo+1 share color
}
