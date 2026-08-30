#include <bits/stdc++.h>
using namespace std;

long long countDigit(long long M, int d){
    if(M<0) return 0;
    long long count=0;
    for(long long p=1; p<=M; p*=10){
        long long higher = M/(p*10);
        long long cur = (M/p)%10;
        long long lower = M%p;
        if(d==0){
            if(higher==0) continue;
            count += (higher-1)*p;
            if(cur>0) count += p;
            else count += lower+1;
        } else {
            count += higher*p;
            if(cur>d) count += p;
            else if(cur==d) count += lower+1;
        }
    }
    return count;
}

bool feasible(long long M, long long n){
    for(int d=0;d<10;d++) if(countDigit(M,d) > n) return false;
    return true;
}

int main(){
    long long n; scanf("%lld",&n);
    long long lo=1, hi=4000000000000000000LL;
    while(lo<hi){
        long long mid = lo + (hi-lo+1)/2;
        if(feasible(mid,n)) lo=mid; else hi=mid-1;
    }
    printf("%lld\n", lo);
}
