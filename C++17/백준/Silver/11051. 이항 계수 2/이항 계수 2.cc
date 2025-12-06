#include <bits/stdc++.h>
using namespace std;
/*
10007로 나눈 나머지 
범위는  1<=N<= 1000
1000!의 범위는 매우 크므로 저장할 수 있는 자료형이 없다.
방법 1 
(x×y)modm=((xmodm)×(ymodm))modm 
각각의 값에 모듈러 연산을 하고 나온 값을 mod연산 수행 

10007은 소수라서 페르마의 정리 가능

방법 2 

이항계수 : n개의 항목 중에서 k개의 항목을 선택하는 방법의 수

n개에서 k를 고르는 경우 
1. 첫 번째 원소를 골랏다면 n-1개에서 k-1개를 고르는 경우
2. 첫 번째 원소를 고르지 않았다면 n-1개에서 k개를 고르는 경우 
두가지를 합하면 된다. => 큰 조건을 작은 조건으로 나눌 수 있다 => DP
경계 조건 (n  0) =1  (n  n) =1 

*/
int N,K;
const int MOD = 10007; // 나눌 값.
int dp[1001][1001];

int main() {
    ios:: sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K; 
    
  for (int n = 0; n <= N; n++) {
        int upto = min(n, K);
        for (int k = 0; k <= upto; k++) {
            if (k == 0 || k == n) dp[n][k] = 1;
            else dp[n][k] = (dp[n - 1][k] + dp[n - 1][k - 1]) % MOD;
        }
    }

    cout << dp[N][K]%MOD ;
    return 0;
}