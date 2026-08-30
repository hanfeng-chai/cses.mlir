#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n, k, x, a, b, c;
    scanf("%lld %lld %lld %lld %lld %lld", &n, &k, &x, &a, &b, &c);
    vector<int> arr(n);
    long long prev = x; arr[0] = (int)x;
    for (long long i = 1; i < n; i++) { prev = (a * prev + b) % c; arr[i] = (int)prev; }
    long long wx = 0;
    for (long long i = 0; i < k; i++) wx ^= arr[i];
    long long ans = wx;
    for (long long i = k; i < n; i++) { wx ^= arr[i] ^ arr[i - k]; ans ^= wx; }  // xor slides reversibly
    printf("%lld\n", ans);
}
