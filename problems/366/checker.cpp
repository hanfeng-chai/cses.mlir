#include "testlib.h"
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    string current = inf.readWord();
    int juryMoves = ans.readInt();
    int moves = ouf.readInt(-1, 1000, "number of moves");

    if ((juryMoves == -1) != (moves == -1)) {
        quitf(_wa, "jury reports %s, participant reports %s",
              juryMoves == -1 ? "impossible" : "possible",
              moves == -1 ? "impossible" : "possible");
    }
    if (moves == -1) quitf(_ok, "correctly impossible");

    int length = 2 * n;
    for (int turn = 1; turn <= moves; ++turn) {
        string next = ouf.readWord();
        if ((int)next.size() != length)
            quitf(_pe, "turn %d: state length %d, expected %d", turn,
                  (int)next.size(), length);

        int empty = current.find('.');
        if (empty + 1 >= length || current[empty + 1] != '.')
            quitf(_fail, "internal input state has non-adjacent empty boxes");
        int source = next.find('.');
        if (source + 1 >= length || next[source + 1] != '.')
            quitf(_wa, "turn %d: new empty boxes are not adjacent", turn);
        if (current[source] == '.' || current[source + 1] == '.')
            quitf(_wa, "turn %d: source boxes did not both contain letters", turn);

        string expected = current;
        swap(expected[empty], expected[source]);
        swap(expected[empty + 1], expected[source + 1]);
        if (next != expected)
            quitf(_wa, "turn %d is not the result of moving one adjacent letter pair", turn);
        current = next;
    }

    string letters;
    for (char ch : current) {
        if (ch != '.') letters.push_back(ch);
    }
    string target(n - 1, 'A');
    target += string(n - 1, 'B');
    if (letters != target)
        quitf(_wa, "final letters are not all A before all B");

    quitf(_ok, "valid solution in %d moves", moves);
}
