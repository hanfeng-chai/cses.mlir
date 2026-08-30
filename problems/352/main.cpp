#include <bits/stdc++.h>
using namespace std;

struct FingerprintHash {
    size_t operator()(const array<int, 26> &value) const noexcept {
        uint64_t hash = 0x9e3779b97f4a7c15ULL;
        for (int x : value) {
            uint64_t z = uint32_t(x) + 0x9e3779b9U;
            z ^= z >> 16;
            z *= 0x85ebca6bU;
            z ^= z >> 13;
            hash ^= z + 0x9e3779b97f4a7c15ULL + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    array<bool, 26> present{};
    for (char ch : s) present[ch - 'a'] = true;
    int reference = 0;
    while (!present[reference]) ++reference;

    array<int, 26> count{};
    array<int, 26> fingerprint{};
    unordered_map<array<int, 26>, int, FingerprintHash> frequency;
    frequency.reserve(2 * s.size() + 1);
    frequency.max_load_factor(0.7f);
    frequency[fingerprint] = 1;

    long long answer = 0;
    for (char ch : s) {
        ++count[ch - 'a'];
        for (int letter = 0; letter < 26; ++letter) {
            fingerprint[letter] = present[letter]
                                      ? count[letter] - count[reference]
                                      : 0;
        }
        auto [it, inserted] = frequency.try_emplace(fingerprint, 0);
        answer += it->second;
        ++it->second;
        (void)inserted;
    }

    cout << answer << '\n';
}
