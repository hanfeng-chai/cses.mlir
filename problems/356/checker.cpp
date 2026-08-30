#include "testlib.h"
using namespace std;

// 356 Water Containers Moves 是多解题：只要求出移动水量之和最小(与裁判一致)的合法操作
// 序列即可，具体每一步怎么走不唯一。
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    long long a = inf.readLong();
    long long b = inf.readLong();
    long long x = inf.readLong();

    string jFirst = ans.readToken();
    bool juryImpossible = (jFirst == "-1");
    long long juryM = -1;
    if (!juryImpossible) juryM = ans.readLong();

    string pFirst = ouf.readToken();
    if (pFirst == "-1") {
        if (!juryImpossible) quitf(_wa, "participant says impossible, but optimal total is %lld", juryM);
        quitf(_ok, "correctly impossible");
    }
    if (juryImpossible) quitf(_wa, "participant claims a solution exists, but it is impossible");

    long long pN = std::stoll(pFirst);
    if (pN < 0) quitf(_wa, "negative move count %lld", pN);
    long long pM = ouf.readLong(0, (long long)4e18, "m");
    if (pM != juryM) quitf(_wa, "total water moved %lld, but optimal is %lld", pM, juryM);

    long long curA = 0, curB = 0, totalMoved = 0;
    for (long long i = 0; i < pN; i++) {
        string act = upperCase(ouf.readToken());
        if (act == "FILL") {
            string who = upperCase(ouf.readToken());
            long long amt;
            if (who == "A") { amt = a - curA; curA = a; }
            else if (who == "B") { amt = b - curB; curB = b; }
            else { quitf(_pe, "bad container '%s' after FILL", who.c_str()); return 0; }
            if (amt <= 0) quitf(_wa, "move %lld (FILL %s) moves 0 units", i + 1, who.c_str());
            totalMoved += amt;
        } else if (act == "EMPTY") {
            string who = upperCase(ouf.readToken());
            long long amt;
            if (who == "A") { amt = curA; curA = 0; }
            else if (who == "B") { amt = curB; curB = 0; }
            else { quitf(_pe, "bad container '%s' after EMPTY", who.c_str()); return 0; }
            if (amt <= 0) quitf(_wa, "move %lld (EMPTY %s) moves 0 units", i + 1, who.c_str());
            totalMoved += amt;
        } else if (act == "MOVE") {
            string from = upperCase(ouf.readToken());
            string to = upperCase(ouf.readToken());
            long long amt;
            if (from == "A" && to == "B") { amt = min(curA, b - curB); curA -= amt; curB += amt; }
            else if (from == "B" && to == "A") { amt = min(curB, a - curA); curB -= amt; curA += amt; }
            else { quitf(_pe, "bad move '%s %s'", from.c_str(), to.c_str()); return 0; }
            if (amt <= 0) quitf(_wa, "move %lld (MOVE %s %s) moves 0 units", i + 1, from.c_str(), to.c_str());
            totalMoved += amt;
        } else {
            quitf(_pe, "unknown action '%s'", act.c_str());
        }
    }

    if (curA != x) quitf(_wa, "final amount in A is %lld, expected %lld", curA, x);
    if (totalMoved != pM) quitf(_wa, "declared total %lld but actual moved water is %lld", pM, totalMoved);

    quitf(_ok, "valid optimal sequence: %lld moves, %lld water", pN, pM);
}
