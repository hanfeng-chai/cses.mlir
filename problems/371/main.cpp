#include <bits/stdc++.h>
using namespace std;

long long gcdll(long long a,long long b){ while(b){ a%=b; swap(a,b); } return a; }

// position after k steps of a 1D bounce in [0,L]
long long bouncePos(long long k, long long L){
    if(L==0) return 0;
    long long period = 2*L;
    long long r = k % period;
    return (r<=L) ? r : (period-r);
}

int main(){
    int t; scanf("%d",&t);
    string out;
    for(int i=0;i<t;i++){
        long long n,m,k; scanf("%lld %lld %lld",&n,&m,&k);
        long long a=n-1, b=m-1;
        long long row = bouncePos(k,a)+1;
        long long col = bouncePos(k,b)+1;
        long long g = gcdll(a,b);
        long long l = a/g*b; // lcm(a,b)
        long long changes = k/a + k/b - k/l;
        out += to_string(row); out+=' ';
        out += to_string(col); out+=' ';
        out += to_string(changes); out+='\n';
    }
    fputs(out.c_str(), stdout);
}
