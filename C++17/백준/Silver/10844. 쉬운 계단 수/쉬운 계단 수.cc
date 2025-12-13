#include <iostream>
#include <vector>

using namespace std;

// 문제에서 요구하는 모듈러 값
const int MOD = 1000000000;

int main() {
    // 입출력 속도 향상
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    // dp[i][j]: 길이가 i이고 마지막 숫자가 j인 계단 수의 개수
    // N은 최대 100이므로 101, j는 0부터 9이므로 10
    vector<vector<long long>> dp(N + 1, vector<long long>(10, 0));

    // 1. 길이 1일 때 (기저 조건)
    // 1자리 계단 수는 1, 2, ..., 9 이므로 9개
    // dp[1][0]은 0이고, dp[1][1] ~ dp[1][9]는 모두 1
    for (int j = 1; j <= 9; j++) {
        dp[1][j] = 1;
    }

    // 2. 길이 2부터 N까지 계산
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j <= 9; j++) {
            if (j == 0) {
                // 마지막 숫자가 0 -> 이전 숫자는 1
                dp[i][0] = dp[i-1][1] % MOD;
            } else if (j == 9) {
                // 마지막 숫자가 9 -> 이전 숫자는 8
                dp[i][9] = dp[i-1][8] % MOD;
            } else {
                // 마지막 숫자가 1~8 -> 이전 숫자는 j-1 또는 j+1
                dp[i][j] = (dp[i-1][j-1] + dp[i-1][j+1]) % MOD;
            }
        }
    }

    // 3. 결과 계산
    // N자리 계단 수의 총합은 dp[N][0] 부터 dp[N][9]까지의 합
    long long total_count = 0;
    for (int j = 0; j <= 9; j++) {
        total_count = (total_count + dp[N][j]) % MOD;
    }

    cout << total_count;

    return 0;
}