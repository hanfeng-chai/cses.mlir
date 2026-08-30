#include <bits/stdc++.h>
using namespace std;

// 395 Mex Grid Queries: computing the recursive "mex of everything to the left
// and above" definition for small grids reveals the value at 0-indexed (y,x) is
// simply y XOR x (verified computationally for a 16x16 grid: e.g. row 2 gives
// [2,3,0,1,6,7,4,5,10,11] which is exactly 2^0,2^1,2^2,2^3,... = y^x). This is
// the classical fact that XOR is the unique operation making every prefix (in
// each row and column) contain all smaller values exactly once, i.e. it's a
// Latin-square-like "Cayley table of the nimber addition group" structure.
int main() {
    long long y, x;
    scanf("%lld %lld", &y, &x);
    printf("%lld\n", (y - 1) ^ (x - 1));
}
