#include <bits/stdc++.h>
using namespace std;
/*
시작 말은 4개 
10, 20 , 30 에서 출발하면 blue dir로 이동 
그 외 혹은 10,20,30 을 지나면 red dir 
도착 하지 않은 말 중에 하나를 골라서 10개의 턴 이후 최대 점수를 얻도록 하자.
이동할때 도착지에 다른 말이 있으면 안됨(마지막 칸 제외)

*/

struct Horse {
    int pos;    // 현재 위치 (start보다는 pos가 직관적입니다)
    int score;  // 획득 점수
    bool arrive; // 도착 여부
};

Horse horses[4]; //자동으로 0,0,false로 초기화 
int ans = 0;
int dice[10];

int board_score[33];      // 각 칸의 점수 저장
int nxt[33];      // 빨간색 화살표 (기본 경로)
int blue[33];     // 파란색 화살표 (꺾이는 경로)
bool on_horse[33];

void init() {
    // 1. 기본 외곽 경로 (0~20번) 및 점수 세팅
    for (int i = 0; i <= 20; i++) {
        board_score[i] = i * 2;
        nxt[i] = i + 1;
    }
    nxt[20] = 32; // 40점(20번) 다음은 도착(32번)
    board_score[32] = 0; // 도착 지점 점수는 0

    // 2. 10번 칸(점수 10)에서 꺾이는 경로 (21~23번)
    board_score[21] = 13; board_score[22] = 16; board_score[23] = 19;
    nxt[21] = 22; nxt[22] = 23; nxt[23] = 29; // 19 다음은 중앙 25(29번)

    // 3. 20번 칸(점수 20)에서 꺾이는 경로 (24~25번)
    board_score[24] = 22; board_score[25] = 24;
    nxt[24] = 25; nxt[25] = 29; // 24 다음은 중앙 25(29번)

    // 4. 30번 칸(점수 30)에서 꺾이는 경로 (26~28번)
    board_score[26] = 28; board_score[27] = 27; board_score[28] = 26;
    nxt[26] = 27; nxt[27] = 28; nxt[28] = 29; // 26 다음은 중앙 25(29번)

    // 5. 중앙(25점) 이후 합쳐지는 공통 경로 (29~31번)
    board_score[29] = 25; board_score[30] = 30; board_score[31] = 35;
    nxt[29] = 30; nxt[30] = 31; nxt[31] = 20; // 35 다음은 40점(20번)

    // 6. 파란색 분기점 세팅 (5, 10, 15번 인덱스)
    blue[5] = 21;  // 10점에서 꺾임
    blue[10] = 24; // 20점에서 꺾임
    blue[15] = 26; // 30점에서 꺾임
}

void play(int t){
    //if(ans<val) return ;
    if(t==10){
        int temp = 0;
        for(int i=0;i<4;i++)temp+= horses[i].score;
        ans = max(ans,temp);
        return ;
    }
    for(int i=0;i<4;i++){
        auto cur = horses[i];
        if(cur.arrive)continue;
        
        int old_pos = cur.pos;
        int next = old_pos;

        // 1. 첫 이동 시 파란색 칸 체크
        if (blue[next] != 0) {
            next = blue[next];
        } else {
            next = nxt[next];
        }
        // 2. 나머지 주사위 눈금만큼 이동
        for (int d = 1; d < dice[t]; d++) {
            if (next == 32) break;
            next = nxt[next];
        }
        //도착은 갈 수 있다.
        if(on_horse[next]&& next!=32) continue;
        //도착이 아니고 도착지에 말이 없는 경우
        //점수 추가 + 위치 이동 +  도착한 경우 
        horses[i].score += board_score[next];
        horses[i].pos = next;
        //말 위치 이동 
        on_horse[cur.pos]=0;
        on_horse[next]=1;
        if(next==32) horses[i].arrive = true;
        play(t+1);
        //복구
        horses[i] = cur;
        on_horse[next]=0;
        on_horse[cur.pos]=1;
        
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i=0;i<10;i++) cin>> dice[i];
    init();
    play(0);
    
    cout<<ans;
    return 0;
}