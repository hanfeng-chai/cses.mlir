#include <bits/stdc++.h>
using namespace std;
const int MX = 200005;
int len_[MX], lnk[MX], to[MX][26], sz, last, N;
char s[MX];
int getLink(int v) { while (s[N - len_[v] - 1] != s[N]) v = lnk[v]; return v; }
int main() {
    string str; cin >> str;
    s[0] = -1; N = 0;
    len_[0] = -1; lnk[0] = 0;  // imaginary root (length -1)
    len_[1] = 0; lnk[1] = 0;   // empty palindrome root
    sz = 2; last = 1;
    string out;
    for (char ch : str) {  // eertree: len of longest palindromic suffix at each step
        s[++N] = ch; int c = ch - 'a';
        int cur = getLink(last);
        if (!to[cur][c]) {
            int now = sz++;
            len_[now] = len_[cur] + 2;
            lnk[now] = (len_[now] == 1) ? 1 : to[getLink(lnk[cur])][c];
            to[cur][c] = now;
        }
        last = to[cur][c];
        out += to_string(len_[last]); out += ' ';
    }
    if (!out.empty()) out.pop_back();
    cout << out << "\n";
}
