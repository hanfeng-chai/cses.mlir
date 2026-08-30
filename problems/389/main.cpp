#include <bits/stdc++.h>
using namespace std;

long long mod_power(long long base, long long exponent, int mod) {
    long long result = 1;
    while (exponent) {
        if (exponent & 1) result = result * base % mod;
        base = base * base % mod;
        exponent >>= 1;
    }
    return result;
}

void ntt(vector<int> &values, bool inverse, int mod, int primitive_root) {
    int n = values.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(values[i], values[j]);
    }

    for (int length = 2; length <= n; length <<= 1) {
        int root = mod_power(primitive_root, (mod - 1) / length, mod);
        if (inverse) root = mod_power(root, mod - 2, mod);
        for (int start = 0; start < n; start += length) {
            long long multiplier = 1;
            for (int i = 0; i < length / 2; ++i) {
                int even = values[start + i];
                int odd = multiplier * values[start + i + length / 2] % mod;
                int sum = even + odd;
                if (sum >= mod) sum -= mod;
                int difference = even - odd;
                if (difference < 0) difference += mod;
                values[start + i] = sum;
                values[start + i + length / 2] = difference;
                multiplier = multiplier * root % mod;
            }
        }
    }

    if (inverse) {
        long long inverse_n = mod_power(n, mod - 2, mod);
        for (int &value : values) value = value * inverse_n % mod;
    }
}

vector<int> convolution(const vector<int> &left, const vector<int> &right,
                        int size, int mod, int primitive_root) {
    vector<int> a(size), b(size);
    copy(left.begin(), left.end(), a.begin());
    copy(right.begin(), right.end(), b.begin());
    ntt(a, false, mod, primitive_root);
    ntt(b, false, mod, primitive_root);
    for (int i = 0; i < size; ++i) a[i] = (long long)a[i] * b[i] % mod;
    ntt(a, true, mod, primitive_root);
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string bits;
    cin >> bits;
    int n = bits.size();
    vector<int> frequency(n + 1, 0);
    int prefix = 0;
    ++frequency[0];
    for (char bit : bits) {
        prefix += bit == '1';
        ++frequency[prefix];
    }

    long long zero_ones = 0;
    for (int count : frequency) zero_ones += 1LL * count * (count - 1) / 2;

    vector<int> reversed(n + 1);
    for (int i = 0; i <= n; ++i) reversed[n - i] = frequency[i];
    int transform_size = 1;
    while (transform_size < 2 * n + 1) transform_size <<= 1;

    constexpr int MOD1 = 998244353;
    constexpr int MOD2 = 1004535809;
    vector<int> product1 = convolution(frequency, reversed, transform_size, MOD1, 3);
    vector<int> product2 = convolution(frequency, reversed, transform_size, MOD2, 3);
    long long inverse_mod1 = mod_power(MOD1, MOD2 - 2, MOD2);

    cout << zero_ones;
    for (int ones = 1; ones <= n; ++ones) {
        long long residue1 = product1[n + ones];
        long long delta = product2[n + ones] - residue1;
        delta %= MOD2;
        if (delta < 0) delta += MOD2;
        long long multiplier = (__int128)delta * inverse_mod1 % MOD2;
        long long exact = residue1 + (long long)MOD1 * multiplier;
        cout << ' ' << exact;
    }
    cout << '\n';
}
