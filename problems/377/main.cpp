#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; scanf("%d",&n);
    vector<long long> a(n), b(n);
    for(auto&v:a) scanf("%lld",&v);
    for(auto&v:b) scanf("%lld",&v);

    vector<long long> P(n);
    long long run=0;
    for(int i=0;i<n;i++){ run += a[i]-b[i]; P[i]=run; }

    vector<long long> sorted_P(P);
    sort(sorted_P.begin(), sorted_P.end());
    long long median = sorted_P[n/2];

    long long cost=0;
    for(int i=0;i<n;i++) cost += llabs(median - P[i]);
    printf("%lld\n", cost);
}
