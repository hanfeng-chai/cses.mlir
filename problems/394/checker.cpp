#include "testlib.h"
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    map<long long, int> available;
    for (int i = 0; i < n; ++i) ++available[inf.readLong()];

    string juryFirst = ans.readWord();
    bool juryImpossible = juryFirst == "IMPOSSIBLE";
    string first = ouf.readWord();
    if (first == "IMPOSSIBLE") {
        if (!juryImpossible) quitf(_wa, "participant reports impossible, but a solution exists");
        quitf(_ok, "correctly impossible");
    }
    if (juryImpossible) quitf(_wa, "jury reports impossible, but participant gives subsets");

    int firstSize;
    try {
        firstSize = stoi(first);
    } catch (...) {
        quitf(_pe, "expected subset size, got '%s'", first.c_str());
    }
    if (firstSize < 1 || firstSize > n) quitf(_wa, "invalid first subset size %d", firstSize);

    long long firstSum = 0, secondSum = 0;
    for (int i = 0; i < firstSize; ++i) {
        long long value = ouf.readLong();
        if (available[value] == 0) quitf(_wa, "value %lld is unavailable in first subset", value);
        --available[value];
        firstSum += value;
    }

    int secondSize = ouf.readInt(1, n, "second subset size");
    for (int i = 0; i < secondSize; ++i) {
        long long value = ouf.readLong();
        if (available[value] == 0) quitf(_wa, "value %lld is unavailable in second subset", value);
        --available[value];
        secondSum += value;
    }

    if (firstSum != secondSum)
        quitf(_wa, "subset sums differ: %lld versus %lld", firstSum, secondSum);
    quitf(_ok, "valid disjoint subsets with sum %lld", firstSum);
}
