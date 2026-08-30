#include <bits/stdc++.h>
using namespace std;

long long floordiv(long long a, long long b){
    long long q=a/b, r=a%b;
    if(r!=0 && ((r<0)!=(b<0))) q--;
    return q;
}

long long knightDist(long long dx, long long dy){
    dx=llabs(dx); dy=llabs(dy);
    if(dx<dy) swap(dx,dy);
    if(dx==1 && dy==0) return 3;
    if(dx==2 && dy==2) return 4;
    long long delta = dx-dy;
    if(dy>delta) return delta - 2*floordiv(delta-dy, 3);
    else return delta - 2*floordiv(delta-dy, 4);
}

int main(){
    int n; scanf("%d",&n);
    string out;
    for(int i=0;i<n;i++){
        long long x,y; scanf("%lld %lld",&x,&y);
        long long d;
        if(x==2 && y==2) d=4; // board is a quarter-plane (x,y>=1); the infinite-board
                               // shortcut through negative coordinates is blocked here
        else d = knightDist(x-1, y-1);
        out += to_string(d); out += '\n';
    }
    fputs(out.c_str(), stdout);
}
