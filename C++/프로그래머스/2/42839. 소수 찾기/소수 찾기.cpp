#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAX = 10000000;
bool is_not_prime[MAX]; // 전역 배열 (기본값 false: 소수임)
bool prime_initialized = false;

// 에라토스테네스의 체를 단 한 번만 실행하는 전처리 함수
void init_prime() {
    if (prime_initialized) return;
    
    is_not_prime[0] = is_not_prime[1] = true; // 0과 1은 소수가 아님
    for (int i = 2; i * i < MAX; i++) {
        if (!is_not_prime[i]) {
            for (int j = i * i; j < MAX; j += i) {
                is_not_prime[j] = true; // 소수의 배수는 합성수 처리
            }
        }
    }
    prime_initialized = true;
}

int solution(string numbers) {
    // 1. 에라토스테네스의 체 전처리 (프로그램 전체 통틀어 최초 1회만 수행됨)
    init_prime();
    
    set<int> unique_numbers;
    sort(numbers.begin(), numbers.end());
    int n = numbers.length();
    
    // 2. 1개부터 n개까지 뽑는 모든 조합 순회
    for (int r = 1; r <= n; r++) {
        vector<int> idx(n, 0);
        for (int i = 0; i < r; i++) idx[n - i - 1] = 1;
        
        do {
            string s = "";
            for (int i = 0; i < n; i++) {
                if (idx[i]) s += numbers[i];
            }
            
            string sub = s;
            sort(sub.begin(), sub.end());
            do {
                int val = stoi(sub);
                unique_numbers.insert(val); // set으로 중복 제거
            } while (next_permutation(sub.begin(), sub.end()));
            
        } while (next_permutation(idx.begin(), idx.end()));
    }
    
    // 3. 미리 만들어둔 체(is_not_prime)를 이용해 O(1)로 소수 판별
    int answer = 0;
    for (int num : unique_numbers) {
        if (!is_not_prime[num]) { // false이면 소수
            answer++;
        }
    }
    
    return answer;
}