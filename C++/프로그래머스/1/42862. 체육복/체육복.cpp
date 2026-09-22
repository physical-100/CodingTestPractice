#include <bits/stdc++.h>
using namespace std;

bool check[31];
bool real_lost[31];

int solution(int n, vector<int> lost, vector<int> reserve) {
    // 1. 순서대로 정렬 (그리디 핵심)
    sort(lost.begin(), lost.end());
    sort(reserve.begin(), reserve.end());
    
    // 2. 여벌 정보 먼저 세팅
    for(auto idx : reserve)
        check[idx] = true;
        
    // 3. 도난당한 학생 중 여벌이 있던 학생 처리
    for(auto idx : lost){
        if(check[idx]) { 
            check[idx] = false; // 내 여벌은 도난당함 (남에게 빌려줄 수 없음)
            continue; // 나는 남에게 빌릴 필요도 없음
        }
        real_lost[idx] = true; // 진짜로 체육복이 부족한 학생
    }        
    
    int answer = n; // 전체 학생 수에서 시작
    
    // 4. 진짜 부족한 학생들만 체육복 빌리기 시도
    for(int idx = 1; idx <= n; idx++){
        if(!real_lost[idx]) continue;
        
        // 앞사람에게 빌리기 (idx - 1 >= 1)
        if(idx > 1 && check[idx - 1]) {
            check[idx - 1] = false;
            continue;
        }
        // 뒷사람에게 빌리기 (idx + 1 <= n)
        if(idx < n && check[idx + 1]) {
            check[idx + 1] = false;
            continue;
        }
        
        // 둘 다 못 빌리면 수업을 못 들음
        answer--;
    }
    
    return answer;
}