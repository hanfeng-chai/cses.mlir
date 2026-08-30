#include <bits/stdc++.h>
using namespace std;

int main(){
    long long n; scanf("%lld",&n);
    long long target = (n*n+1)/2;
    long long lo=1, hi=n*n;
    while(lo<hi){
        long long mid=lo+(hi-lo)/2;
        long long cnt=0;
        for(long long i=1;i<=n;i++) cnt += min(n, mid/i);
        if(cnt>=target) hi=mid; else lo=mid+1;
    }
    printf("%lld\n", lo);
}
