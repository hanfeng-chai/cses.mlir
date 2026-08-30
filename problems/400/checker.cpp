#include "testlib.h"
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    vector<int> permutation(n);
    for (int &value : permutation) value = inf.readInt();

    string juryFirst = ans.readWord();
    bool juryImpossible = juryFirst == "IMPOSSIBLE";
    string first = ouf.readWord();
    if (first == "IMPOSSIBLE") {
        if (!juryImpossible) quitf(_wa, "participant reports impossible, but a solution exists");
        quitf(_ok, "correctly impossible");
    }
    if (juryImpossible) quitf(_wa, "jury reports impossible, but participant gives stack labels");

    vector<int> label(n);
    try {
        label[0] = stoi(first);
    } catch (...) {
        quitf(_pe, "expected stack label, got '%s'", first.c_str());
    }
    if (label[0] < 1 || label[0] > 2) quitf(_pe, "invalid stack label %d", label[0]);
    for (int i = 1; i < n; ++i) label[i] = ouf.readInt(1, 2, "stack label");

    vector<int> stacks[2];
    int expected = 1;
    for (int i = 0; i < n; ++i) {
        stacks[label[i] - 1].push_back(permutation[i]);
        while (true) {
            if (!stacks[0].empty() && stacks[0].back() == expected) {
                stacks[0].pop_back();
                ++expected;
            } else if (!stacks[1].empty() && stacks[1].back() == expected) {
                stacks[1].pop_back();
                ++expected;
            } else {
                break;
            }
        }
    }
    if (expected != n + 1)
        quitf(_wa, "assigned stacks cannot produce the sorted output (stuck before %d)", expected);
    quitf(_ok, "valid two-stack assignment");
}
