#include <bits/stdc++.h>
using namespace std;
/*
비용의 제곱이 1000000보다 작다 -> 음수 값도 가능. 
*/
const int limit  = 1e9;
int graph[100001][3];
int dp[100001][3];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int cnt = 0;
    while(1){
        int n;
        cin >>n;
        if(n==0) break;
        for(int i=0;i<n;i++)
            for(int j=0;j<3;j++){
                cin>> graph[i][j];
                dp[i][j] = limit;
            }
        //첫번째 행 초기화 
        dp[0][1] = graph[0][1];
        dp[0][2] = graph[0][1]+graph[0][2];
        
        for(int i=1;i<n;i++){
            // 왼쪽 칸 (j=0)
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + graph[i][0];
            
            // 가운데 칸 (j=1)
            dp[i][1] = min({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2], dp[i][0]}) + graph[i][1];
            
            // 오른쪽 칸 (j=2)
            dp[i][2] = min({dp[i - 1][1], dp[i - 1][2], dp[i][1]}) + graph[i][2];
        }
        cout<<++cnt<<". "<<dp[n-1][1]<<'\n';
    }
    return 0;
}