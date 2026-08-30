#include <bits/stdc++.h>
using namespace std;
const long long MOD=1e9+7;
int main(){
    int n; scanf("%d",&n);
    // Hertzsprung: a(0)=1,a(1)=1,a(2)=0,a(3)=0; a(n)=(n+1)a(n-1)-(n-2)a(n-2)-(n-5)a(n-3)+(n-3)a(n-4)
    vector<long long> a(max(4,n+1),0);
    a[0]=1; if(n>=1)a[1]=1; if(n>=2)a[2]=0; if(n>=3)a[3]=0;
    for(int i=4;i<=n;i++){
        long long v=((long long)(i+1)%MOD*a[i-1] - (long long)(i-2)%MOD*a[i-2] - (long long)(i-5)%MOD*a[i-3] + (long long)(i-3)%MOD*a[i-4])%MOD;
        v%=MOD; if(v<0)v+=MOD; a[i]=v;
    }
    printf("%lld\n", a[n]%MOD);
}
