#include "testlib.h"
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    long long target = inf.readLong();
    string jury = ans.readWord();
    string candidate = ouf.readWord();

    if (candidate.size() != jury.size())
        quitf(_wa, "length %d, but minimum length is %d",
              (int)candidate.size(), (int)jury.size());

    long long endingZeroPlusOne = 1;
    long long endingOnePlusOne = 1;
    for (char bit : candidate) {
        if (bit == '0') endingZeroPlusOne += endingOnePlusOne;
        else if (bit == '1') endingOnePlusOne += endingZeroPlusOne;
        else quitf(_pe, "invalid character '%c'", bit);
        if (endingZeroPlusOne + endingOnePlusOne - 2 > target)
            quitf(_wa, "number of distinct subsequences already exceeds target");
    }
    long long count = endingZeroPlusOne + endingOnePlusOne - 2;
    if (count != target)
        quitf(_wa, "string has %lld distinct nonempty subsequences, expected %lld", count, target);

    quitf(_ok, "valid minimum-length string of length %d", (int)candidate.size());
}
