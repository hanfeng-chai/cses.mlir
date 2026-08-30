#include "testlib.h"
using namespace std;

// 370 List of Sums 是多解题：只要构造出的数组的两两之和的多重集与输入 B 完全一致即可，
// 元素顺序、具体取值不必和裁判一致。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int m = n * (n - 1) / 2;
    vector<long long> B(m);
    for (auto &v : B) v = inf.readLong();
    sort(B.begin(), B.end());

    vector<long long> A(n);
    for (auto &v : A) v = ouf.readLong(1, (long long)4e9, "a_i");

    vector<long long> got;
    got.reserve(m);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            got.push_back(A[i] + A[j]);
    sort(got.begin(), got.end());

    if (got != B)
        quitf(_wa, "the pairwise sums of the printed array do not match the given list B");

    quitf(_ok, "valid array of %d elements", n);
}
