#include <bits/stdc++.h>
using namespace std;

/*
    이친수는 0으로 시작하지 않음 
    1이 두번 연속 나타나지 않음 
    N자리 이친수의 개수를 나타내라. 
*/

int n;
long long dp[91];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> n;
    dp[1]=1;
    dp[2]=1;
    for(int i=3;i<=n;i++){
        dp[i] =dp[i-1]+dp[i-2];
    }
    cout<<dp[n];
    return 0;
}