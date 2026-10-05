#include<bits/stdc++.h>

using namespace std;

int solution(int N, int number) {
    if(N==number) return 1;
    int answer = 0;
    vector<unordered_set<int>> dp(9);
    for(int i=1;i<=8;i++){
        int base =0;
        for(int j=0; j<i;j++)
            base = base*10 + N;
        dp[i].insert(base);
        for(int j=1;j<i;j++){
            for(int op1: dp[j]){
                for(int op2: dp[i-j]){
                    dp[i].insert(op1-op2);
                    dp[i].insert(op1+op2);
                    dp[i].insert(op1*op2);
                    if(op2!=0) dp[i].insert(op1/op2);
                }
            }
        } 
        if(dp[i].count(number)) return i;
    }
    return -1;
}