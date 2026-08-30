#include <bits/stdc++.h>
using namespace std;
int main() {
    int lo = 1, hi = 1000000000;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        printf("? %d\n", mid); fflush(stdout);
        char buf[8]; scanf("%s", buf);
        if (buf[0] == 'Y') lo = mid + 1;  // mid < x
        else hi = mid;                    // mid >= x
    }
    printf("! %d\n", lo); fflush(stdout);
}
