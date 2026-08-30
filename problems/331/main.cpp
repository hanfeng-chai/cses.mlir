#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    int n,k; scanf("%d %d",&n,&k);
    // dp[j] = number of permutations of i elements with j inversions
    vector<long long> dp(k+1,0); dp[0]=1; // i=1
    vector<long long> pre(k+2,0);
    for(int i=2;i<=n;i++){
        pre[0]=0;
        for(int j=0;j<=k;j++) pre[j+1]=(pre[j]+dp[j])%MOD;
        // newdp[j] = sum dp[j-i+1 .. j] = pre[j+1]-pre[max(0,j-i+1)]
        vector<long long> nd(k+1,0);
        for(int j=0;j<=k;j++){
            int lo=j-i+1; if(lo<0)lo=0;
            nd[j]=(pre[j+1]-pre[lo]+MOD)%MOD;
        }
        dp.swap(nd);
    }
    printf("%lld\n", dp[k]%MOD);
}
