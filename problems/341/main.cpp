#include <bits/stdc++.h>
using namespace std;

int main(){
    static char buf[1000006];
    scanf("%s", buf);
    string s(buf);
    int n=(int)s.size();
    const string alpha="ACGT";

    vector<array<int,4>> nxt(n+1);
    nxt[n] = {n,n,n,n};
    for(int i=n-1;i>=0;i--){
        nxt[i]=nxt[i+1];
        nxt[i][alpha.find(s[i])] = i;
    }

    vector<int> f(n+1), choice(n+1);
    for(int i=n;i>=0;i--){
        int best=INT_MAX, bestC=0;
        for(int c=0;c<4;c++){
            int val = (nxt[i][c]==n) ? 1 : 1+f[nxt[i][c]+1];
            if(val<best){ best=val; bestC=c; }
        }
        f[i]=best; choice[i]=bestC;
    }

    string res;
    int pos=0;
    while(true){
        int c=choice[pos];
        res += alpha[c];
        if(nxt[pos][c]==n) break;
        pos = nxt[pos][c]+1;
    }
    printf("%s\n", res.c_str());
}
