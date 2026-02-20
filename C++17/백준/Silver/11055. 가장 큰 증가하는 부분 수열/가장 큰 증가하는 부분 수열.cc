#include <bits/stdc++.h>
using namespace std;
int n;
int arr[1001];
long long dp[1001];
//증가하는 부분 수열 -> 값이 더 커지는 것! 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> n;
    for(int i=0;i<n;i++){
        cin>> arr[i];
        dp[i] = arr[i];
    } 
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(arr[j]<arr[i]){
                dp[i] = max(dp[i],dp[j]+arr[i]);
            }
        }
    }
    cout<<*max_element(dp,dp+n);
    return 0;
}