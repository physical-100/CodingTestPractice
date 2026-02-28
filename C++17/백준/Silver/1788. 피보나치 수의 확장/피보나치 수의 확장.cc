#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000000;
int n;
long long dp[1000001];


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    int abs_n =  abs(n);
    
    dp[0] = 0;
    dp[1] = 1;
    for(int i=2;i<=abs_n;i++)
        dp[i] = (dp[i-1]+dp[i-2])%mod;
    
    if(n<0&& abs_n%2==0)cout<<-1<<'\n';
    else if(n==0) cout<<0<<'\n';
    else cout<<1<<'\n';
    cout<<dp[abs_n];
    return 0;
}