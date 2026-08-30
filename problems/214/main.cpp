#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string L; cin >> L; int N = L.size();
    // inverse Burrows-Wheeler transform via LF-mapping
    vector<int> start(128, 0), cntc(128, 0);
    for (char c : L) cntc[(int)c]++;
    int run = 0;
    for (int c = 0; c < 128; c++) { start[c] = run; run += cntc[c]; }
    vector<int> occ(128, 0), LF(N);
    for (int i = 0; i < N; i++) { LF[i] = start[(int)L[i]] + occ[(int)L[i]]; occ[(int)L[i]]++; }
    int j = 0;
    for (int i = 0; i < N; i++) if (L[i] == '#') { j = i; break; }
    string T; T.reserve(N);
    int i = j;
    for (int k = 0; k < N; k++) { i = LF[i]; T.push_back(L[i]); }
    reverse(T.begin(), T.end());  // T becomes "#" + original
    cout << T.substr(1) << "\n";
}
