#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;

int main(){
    int n; scanf("%d",&n);
    vector<long long> x(n);
    for(auto&v:x) scanf("%lld",&v);

    vector<long long> dp(n+1,0), S(n+1,0);
    dp[0]=1; S[0]=1;
    unordered_map<long long,int> last;
    last.reserve(n*2);
    int lo=0;
    for(int i=0;i<n;i++){
        auto it=last.find(x[i]);
        if(it!=last.end()) lo = max(lo, it->second+1);
        last[x[i]] = i;
        long long sum = S[i] - (lo>0 ? S[lo-1] : 0);
        sum %= MOD; if(sum<0) sum+=MOD;
        dp[i+1]=sum;
        S[i+1] = (S[i]+dp[i+1])%MOD;
    }
    printf("%lld\n", dp[n]);
}
