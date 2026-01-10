#include <bits/stdc++.h>
using namespace std ;
/*
1: 채널 업 
2:  채널 다운 
3: 현재 선택한 채널 을 아래로 한칸 내림 화살표는 그대로(위차 변환)
4: 현재 선택한 채널을 한칸 올린다 (위치 변환)

화살표가 리스트 범위를 벗어나면 명령 무시
kbs1이 1번 kbs2가 2번으로 바꾸는 프로그램

방법의 길이는 500이하 

채널수 : 100 이하
채널 이름은 10글자  알파벳 대문자와 숫자로만 이루어짐 
출력 눌러야하는 버튼을 순서대로 공백 없이 출력 
*/
int main() {
    int N;
    cin >> N;

    vector<string> channels(N);
    int kbs1_idx = 0, kbs2_idx = 0;

    for (int i = 0; i < N; i++) {
        cin >> channels[i];
        if (channels[i] == "KBS1") kbs1_idx = i;
        if (channels[i] == "KBS2") kbs2_idx = i;
    }

    // 1. KBS1을 첫 번째(0번)로 이동
    // 커서를 KBS1까지 내림 (1번 조작)
    for (int i = 0; i < kbs1_idx; i++) {
        cout << "1";
    }
    // KBS1을 맨 위로 올림 (3번 조작)
    for (int i = 0; i < kbs1_idx; i++) {
        cout << "4";
    }

    // KBS1이 맨 위로 올라갔으므로, 만약 KBS2가 KBS1보다 위에 있었다면 인덱스가 1 밀림
    if (kbs1_idx > kbs2_idx) kbs2_idx++;

    // 2. KBS2를 두 번째(1번)로 이동
    // 커서를 KBS2까지 내림 (1번 조작)
    for (int i = 0; i < kbs2_idx; i++) {
        cout << "1";
    }
    // KBS2를 두 번째 칸까지 올림 (3번 조작)
    // 0번은 KBS1 자리이므로 i < kbs2_idx - 1 까지만 수행
    for (int i = 0; i < kbs2_idx - 1; i++) {
        cout << "4";
    }

    cout << endl;

    return 0;
}