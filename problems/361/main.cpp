#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<long long> PA(n+1,0), PB(n+1,0);
    for(int i=1;i<=n;i++){ long long v; scanf("%lld",&v); PA[i]=PA[i-1]+v; }
    for(int i=1;i<=n;i++){ long long v; scanf("%lld",&v); PB[i]=PB[i-1]+v; }

    double lo=0, hi=2e9;
    for(int iter=0; iter<200; iter++){
        double mid=(lo+hi)/2;
        double bestA=-1e30;
        for(int i=1;i<=n;i++) bestA=max(bestA, (double)PA[i]-mid*i);
        double bestB=-1e30;
        for(int j=1;j<=n;j++) bestB=max(bestB, (double)PB[j]-mid*j);
        if(bestA+bestB>=0) lo=mid; else hi=mid;
    }
    double V=lo;
    int bi=1,bj=1; double bestA=-1e30, bestB=-1e30;
    for(int i=1;i<=n;i++){ double v=(double)PA[i]-V*i; if(v>bestA){ bestA=v; bi=i; } }
    for(int j=1;j<=n;j++){ double v=(double)PB[j]-V*j; if(v>bestB){ bestB=v; bj=j; } }
    printf("%d %d\n", bi, bj);
}
