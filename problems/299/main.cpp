#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m; scanf("%d %d",&n,&m);
    string out; out.reserve((size_t)m*8);
    for(int i=0;i<m;i++){int a,b;scanf("%d %d",&a,&b);
        if(a<b){out+=to_string(a);out+=' ';out+=to_string(b);}
        else {out+=to_string(b);out+=' ';out+=to_string(a);}
        out+='\n';}
    fputs(out.c_str(),stdout);
}
