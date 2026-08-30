#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n, k, x, a, b, c;
    scanf("%lld %lld %lld %lld %lld %lld", &n, &k, &x, &a, &b, &c);
    vector<int> arr(n);
    long long prev = x; arr[0] = (int)x;
    for (long long i = 1; i < n; i++) { prev = (a * prev + b) % c; arr[i] = (int)prev; }
    long long s = 0;
    for (long long i = 0; i < k; i++) s += arr[i];
    long long ans = s;
    for (long long i = k; i < n; i++) { s += (long long)arr[i] - arr[i - k]; ans ^= s; }
    printf("%lld\n", ans);
}
