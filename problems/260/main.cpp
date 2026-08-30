#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n, k, x, a, b, c;
    scanf("%lld %lld %lld %lld %lld %lld", &n, &k, &x, &a, &b, &c);
    vector<int> arr(n);
    long long prev = x; arr[0] = (int)x;
    for (long long i = 1; i < n; i++) { prev = (a * prev + b) % c; arr[i] = (int)prev; }
    vector<int> dq(n); int head = 0, tail = 0;  // monotonic deque of indices (increasing values)
    long long ans = 0;
    for (long long i = 0; i < n; i++) {
        while (tail > head && arr[dq[tail - 1]] >= arr[i]) tail--;
        dq[tail++] = (int)i;
        if (dq[head] <= i - k) head++;
        if (i >= k - 1) ans ^= arr[dq[head]];
    }
    printf("%lld\n", ans);
}
