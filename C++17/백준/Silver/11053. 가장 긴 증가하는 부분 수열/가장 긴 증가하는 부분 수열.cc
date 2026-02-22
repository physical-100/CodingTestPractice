#include <bits/stdc++.h>
using namespace std;

int n;
int arr[1001];
int dp[1001];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
        cin>> arr[i];
        dp[i]=1;
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(arr[j]<arr[i])
                dp[i] =max(dp[j]+1,dp[i]);
        }
    }
    cout<<*max_element(dp,dp+n);
    return 0;
}