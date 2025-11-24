#include <bits/stdc++.h>
using namespace std;

int n ; 
int step[301];
int DP[301][3];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i=1;i<n+1;i++) cin >> step[i];
    DP[1][1]=step[1];
    
    if (n>= 2) {
        // 2번째 계단 초기화
        //1번째를 건너뛰고 2번째 밟음
        DP[2][1] = step[2];
        
        //1번째를 밟고 2번째 밟음 (연속 2번)
        DP[2][2] = step[2] + DP[1][1];
    }
    for(int i=3;i<=n;i++){
        //점화식  한칸을 뛰거나 두칸을 뛰거나 
        
        //i-2에서 점프
        // i-2를 밟았을 때 연속 1번이었든 2번이었든 상관 없음.
        DP[i][1] = step[i] + max(DP[i-2][1], DP[i-2][2]);
        
        //i-1에서 한 칸 이동 (반드시 연속이여야한다 -> [2])
        DP[i][2] = step[i] + DP[i-1][1];
    }
    
    cout << max(DP[n][1],DP[n][2]);
    return 0;
}