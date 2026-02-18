#include <bits/stdc++.h>
using namespace std;

int n;
int ans;

int pyramid[501][1002];
int dp[501][1002];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> n;
    //피라미드 배열 채우기 
    for(int i=0;i<n;i++){
        for(int j=0;j<i+1;j++){
            cin>>pyramid[i][n-i+2*j];
        }
    }
    dp[0][n] = pyramid[0][n];
    for(int i=1;i<n;i++){
        for(int j=n-i;j<=n+i;j+=2){
            int left =0, right=0;
            if(j-1>0) left=dp[i-1][j-1];
            if(j+1<2*n) right=dp[i-1][j+1];
            dp[i][j] = max(left,right)+ pyramid[i][j];
        }
    }
    cout<< *max_element(dp[n-1]+1,dp[n-1]+2*n);

    
    return 0;
}