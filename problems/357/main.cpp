#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    for(int i=0;i<n;i++){
        long long a,b,x; scanf("%lld %lld %lld",&a,&b,&x);
        long long g = std::gcd(a,b);
        bool ok = (x<=a) && (x%g==0);
        puts(ok ? "YES" : "NO");
    }
}
