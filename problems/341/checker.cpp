#include "testlib.h"
using namespace std;

// 341 Shortest Subsequence 是多解题：任何“最短的、不是原串子序列”的 ACGT 串都算对。
// 用 ans 文件里裁判给出的最优解长度作为最短长度的基准，只检查参赛输出的长度是否达到
// 该最优长度，以及它确实不是输入串的子序列。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    string s = inf.readWord();
    string jans = ans.readWord();
    string pans = ouf.readWord();

    for (char c : pans) {
        if (c != 'A' && c != 'C' && c != 'G' && c != 'T')
            quitf(_wa, "output contains a character other than A/C/G/T: '%c'", c);
    }
    if (pans.size() != jans.size())
        quitf(_wa, "length %d, but optimal length is %d", (int)pans.size(), (int)jans.size());

    size_t si = 0, ti = 0;
    while (si < s.size() && ti < pans.size()) {
        if (s[si] == pans[ti]) ti++;
        si++;
    }
    if (ti == pans.size())
        quitf(_wa, "the output IS a subsequence of the input (it must not be)");

    quitf(_ok, "valid shortest non-subsequence, length %d", (int)pans.size());
}
