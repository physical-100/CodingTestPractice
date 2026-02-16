#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second

/*
피보나치 함수를 실행했을 때 0과 1이 각각 몇번 출력되는지 구하라 
*/
int t;
pair<int,int> dp[41];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    dp[0] = {1,0};
    dp[1] = {0,1};
    for(int i=2;i<41;i++){
        dp[i] = {dp[i-1].X+dp[i-2].X , dp[i-1].Y+dp[i-2].Y};
    }
    while(t--){
        int n;
        cin >> n;
        cout << dp[n].X<<' ' <<dp[n].Y<<'\n';
    }
    return 0;
}