#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    long long S = n * (n + 1) / 2;
    if (S % 2) { cout << "NO\n"; return 0; }

    long long target = S / 2;
    vector<char> inA(n + 1, 0);
    for (long long i = n; i >= 1 && target > 0; i--)
        if (target >= i) { inA[i] = 1; target -= i; }  // 贪心从大到小

    vector<long long> A, B;
    for (long long i = 1; i <= n; i++) (inA[i] ? A : B).push_back(i);

    cout << "YES\n" << A.size() << '\n';
    for (size_t i = 0; i < A.size(); i++) cout << A[i] << " \n"[i + 1 == A.size()];
    cout << B.size() << '\n';
    for (size_t i = 0; i < B.size(); i++) cout << B[i] << " \n"[i + 1 == B.size()];
}
