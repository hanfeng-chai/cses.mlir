#include "testlib.h"
using namespace std;

// 012 Palindrome Reorder 是多解题：把字符重排成任意回文，或 "NO SOLUTION"。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    string s = inf.readWord();
    int cnt[26] = {0};
    for (char c : s) cnt[c - 'A']++;
    int odd = 0;
    for (int i = 0; i < 26; i++) if (cnt[i] & 1) odd++;
    bool possible = (odd <= 1);

    string out = ouf.readWord();
    if (!possible) {
        string b = ouf.readWord();
        if (upperCase(out) == "NO" && upperCase(b) == "SOLUTION") quitf(_ok, "NO SOLUTION");
        quitf(_wa, "expected 'NO SOLUTION', got '%s %s'", out.c_str(), b.c_str());
    }
    int n = (int)out.size();
    for (int i = 0, j = n - 1; i < j; i++, j--)
        if (out[i] != out[j]) quitf(_wa, "output is not a palindrome");
    int c2[26] = {0};
    for (char c : out) {
        if (c < 'A' || c > 'Z') quitf(_wa, "invalid char '%c'", c);
        c2[c - 'A']++;
    }
    for (int i = 0; i < 26; i++)
        if (cnt[i] != c2[i]) quitf(_wa, "char '%c' count mismatch", 'A' + i);
    quitf(_ok, "valid palindrome (len %d)", n);
}
