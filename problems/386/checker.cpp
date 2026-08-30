#include "testlib.h"
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    multiset<int> numbers;
    for (int i = 0; i < n; ++i) numbers.insert(inf.readInt());

    int juryFirst = ans.readInt();
    int participantFirst = ouf.readInt(-1, 1000, "first value or -1");
    if ((juryFirst == -1) != (participantFirst == -1)) {
        quitf(_wa, "jury reports %s, participant reports %s",
              juryFirst == -1 ? "impossible" : "possible",
              participantFirst == -1 ? "impossible" : "possible");
    }
    if (participantFirst == -1) quitf(_ok, "correctly impossible");

    auto erase_one = [&](int value, int step) {
        auto it = numbers.find(value);
        if (it == numbers.end())
            quitf(_wa, "step %d: value %d is not present", step, value);
        numbers.erase(it);
    };

    for (int step = 1; step <= n - 1; ++step) {
        int a = step == 1 ? participantFirst : ouf.readInt(0, 1000, "a");
        int b = ouf.readInt(0, 1000, "b");
        erase_one(a, step);
        erase_one(b, step);
        numbers.insert(abs(a - b));
    }

    if (numbers.size() != 1 || *numbers.begin() != 0)
        quitf(_wa, "final multiset does not contain exactly one zero");
    quitf(_ok, "valid sequence of %d operations", n - 1);
}
