#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> tails;  // tails[k] = smallest possible tail of an increasing subseq of length k+1
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        auto it = lower_bound(tails.begin(), tails.end(), x);  // strict increase
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    cout << tails.size() << "\n";
}
