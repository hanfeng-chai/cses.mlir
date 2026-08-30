#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;

int main(){
    int n,a; scanf("%d %d",&n,&a);
    vector<int> x(n);
    for(auto&v:x) scanf("%d",&v);

    // y_i = x_i - a ; want # nonempty subsets with sum(y_i) == 0
    int OFFSET = n*500 + 5;
    int SIZE = 2*OFFSET+1;
    vector<long long> dp(SIZE, 0);
    dp[OFFSET] = 1; // empty subset, sum 0

    for(int i=0;i<n;i++){
        int y = x[i]-a;
        if(y>=0){
            for(int s=SIZE-1; s>=y; s--)
                if(dp[s-y]) dp[s] = (dp[s]+dp[s-y])%MOD;
        } else {
            for(int s=0; s<SIZE+y; s++)
                if(dp[s-y]) dp[s] = (dp[s]+dp[s-y])%MOD;
        }
    }

    long long ans = dp[OFFSET] - 1; // exclude the empty subset
    ans = ((ans%MOD)+MOD)%MOD;
    printf("%lld\n", ans);
}
