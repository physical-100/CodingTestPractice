#include <bits/stdc++.h>

using namespace std;

int solution(int N, int number) {
    if (N == number) return 1;

    // dp[i] : N을 i번 사용해서 만들 수 있는 숫자들의 집합
    vector<unordered_set<int>> dp(9);

    for (int i = 1; i <= 8; i++) {
        // 1. 이어 붙이기 숫자 넣기 (예: N=5일 때 5, 55, 555...)
        int base = 0;
        for (int j = 0; j < i; j++) {
            base = base * 10 + N;
        }
        dp[i].insert(base);

        // 2. 이전 값들의 사칙연산 조합 (j와 i-j로 쪼개기)
        for (int j = 1; j < i; j++) {
            for (int op1 : dp[j]) {
                for (int op2 : dp[i - j]) {
                    dp[i].insert(op1 + op2);
                    dp[i].insert(op1 - op2);
                    dp[i].insert(op1 * op2);
                    if (op2 != 0) dp[i].insert(op1 / op2); // 나누기 0 방지
                }
            }
        }

        // 3. 만약 현재 i단계 집합에 찾고자 하는 number가 있다면 즉시 i 리턴
        if (dp[i].count(number)) {
            return i;
        }
    }

    // 8번 안에 못 찾으면 -1 리턴
    return -1;
}