#include <bits/stdc++.h>
using namespace std;
// sliding-window OR via two stacks (each keeps the OR of its elements)
int main() {
    long long n, k, x, a, b, c;
    scanf("%lld %lld %lld %lld %lld %lld", &n, &k, &x, &a, &b, &c);
    vector<int> arr(n);
    long long prev = x; arr[0] = (int)x;
    for (long long i = 1; i < n; i++) { prev = (a * prev + b) % c; arr[i] = (int)prev; }
    vector<int> inVal(n), inOr(n), outVal(n), outOr(n);
    int inTop = 0, outTop = 0;
    long long ans = 0;
    long long l = 0;
    for (long long r = 0; r < n; r++) {
        int v = arr[r];
        inVal[inTop] = v; inOr[inTop] = (inTop ? inOr[inTop - 1] : 0) | v; inTop++;
        if (r - l + 1 > k) {  // pop oldest (front)
            if (outTop == 0) { while (inTop) { int vv = inVal[--inTop]; outVal[outTop] = vv; outOr[outTop] = (outTop ? outOr[outTop - 1] : 0) | vv; outTop++; } }
            outTop--;
            l++;
        }
        if (r - l + 1 == k) {  // window full: OR of whole queue
            int cur = (outTop ? outOr[outTop - 1] : 0) | (inTop ? inOr[inTop - 1] : 0);
            ans ^= cur;
        }
    }
    printf("%lld\n", ans);
}
