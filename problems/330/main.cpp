#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    char buf[505]; scanf("%s",buf);
    string s=buf; int n=s.size();
    int P=n/2;
    vector<vector<long long>> C(P+1, vector<long long>(P+1,0));
    for(int i=0;i<=P;i++){ C[i][0]=1; for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD; }
    // dp[i][j] = ways to erase s[i..j]; use dp indexed by (i, length)
    // dp2[i][j]: i..j inclusive. store in 2D, dp[i][j].
    vector<vector<long long>> dp(n+1, vector<long long>(n+1,0));
    auto get=[&](int i,int j)->long long{ if(i>j) return 1; return dp[i][j]; };
    for(int len=2; len<=n; len+=2){
        for(int i=0;i+len-1<n;i++){
            int j=i+len-1;
            long long val=0;
            int p=len/2;
            for(int kk=i+1; kk<=j; kk+=2){
                if(s[kk]==s[i]){
                    long long inside = get(i+1,kk-1);
                    long long rest = get(kk+1,j);
                    if(inside && rest){
                        int R=(j-kk)/2;
                        val=(val + inside*rest%MOD*C[p][R])%MOD;
                    }
                }
            }
            dp[i][j]=val;
        }
    }
    printf("%lld\n", dp[0][n-1]%MOD);
}
