#include <bits/stdc++.h>
using namespace std;

// splitmix64 自定义哈希，防 CSES 的 anti-hash 测试点把 unordered_map 卡成 O(n^2)
struct chash {
    static uint64_t sm(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t F = chrono::steady_clock::now().time_since_epoch().count();
        return sm(x + F);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x;
    cin >> n >> x;
    // 含负数：前缀和 + 哈希计数，统计 pre[r]-pre[l]=x 的对数
    unordered_map<long long, long long, chash> cnt;
    cnt.reserve(1 << 18);
    cnt[0] = 1;
    long long pre = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        pre += a;
        auto it = cnt.find(pre - x);
        if (it != cnt.end()) ans += it->second;
        cnt[pre]++;
    }
    cout << ans << '\n';
}
