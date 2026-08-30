#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    // diagonal lengths i+j=s, s=2..2n; split by parity
    vector<int> ga, gb;
    for(int s=2;s<=2*n;s++){ int len=min(s-1, 2*n+1-s); if(s&1) ga.push_back(len); else gb.push_back(len); }
    sort(ga.begin(),ga.end()); sort(gb.begin(),gb.end());
    auto poly=[&](vector<int>&grp){
        vector<long long> dp(grp.size()+1,0); dp[0]=1; int cur=0;
        for(int L: grp){ for(int j=cur;j>=0;j--){ if(dp[j]&&L-j>0) dp[j+1]=(dp[j+1]+dp[j]*(long long)(L-j))%MOD; } cur++; }
        return dp;
    };
    auto pa=poly(ga), pb=poly(gb);
    // convolve, read coefficient k
    long long ans=0;
    for(int i=0;i<(int)pa.size();i++){ int j=k-i; if(j>=0 && j<(int)pb.size()) ans=(ans+pa[i]*pb[j])%MOD; }
    printf("%lld\n", ans);
}
