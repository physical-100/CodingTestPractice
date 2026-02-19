#include <bits/stdc++.h>
using namespace std;

int n;

/*
연속된 몇개의 수를  선택해서 구할 수 있는 합 중 가장 큰 합을 구하라. 
수는 하나 이상 선택 
임의의 지점 i 에서 새로 시작할지 현재 값을 더할지를 선택한다. 

*/
int num[100000];
int dp[100000];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> n;
    for(int i=0;i<n;i++){
        cin>>num[i];
    }
    dp[0] = num[0];
    for(int i=1;i<n;i++){
        //더한 값과 현재 값 중 더 큰것을 선택 
        dp[i]= max(dp[i-1]+num[i],num[i]);
    }
    cout<<*max_element(dp,dp+n);
    return 0;
}