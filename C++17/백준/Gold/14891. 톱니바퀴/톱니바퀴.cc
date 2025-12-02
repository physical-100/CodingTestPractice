#include <bits/stdc++.h>
using namespace std;

/*
8개의 톱니  -> 4개의톱니 바퀴 
각 톱니는 S,N극 중 하나를 나타낸다. 
톱니바퀴를 K번 회전시키는 것 -> 목적
시계방향,  반시계 방향이 존재  => 한칸을 기준으로 
맞닿은 톱니의 극이 다르면 회전  맞닿은 톱니는 서로 반대 방향으로 회전한다.
극이 같으면 회전 하지 않음. 
극이 다르더라도 한 톱니바퀴가 회전하지 않으면 맞닿은 다른 톱니바퀴도 회전 하지 않음.
최종 톱니바퀴의 상태를 구하라 

1번 톱니 바퀴의 12시 방향 -> t[0][0]이 N이면 0 S면 1점
2번 톱니 바퀴의 12시 방향 -> t[1][0]이 N이면 0 S면 2점
3번 톱니 바퀴의 12시 방향 -> t[2][0]이 N이면 0 S면 4점
4번 톱니 바퀴의 12시 방향 -> t[3][0]이 N이면 0 S면 8점
1번 톱니 2
2번 톱니 6,2
3번 톱니 6,2
4번 톱니 6 
회전하는 톱니의 양 옆이 다 같은 극이면 해당 톱니만 회전

*/
//const int N = 0;
//const int S = 1;
void rotate_clock(int n);
void rotate_counterclock(int n);

int t[4][8]; //연결리스트로 구현하는게 best
int k;
vector<pair<int,int>> v; //회전 시킨 방법 저장 벡터
int rotation_dir[4];


void rotate_clock(int n){

    //배열의 마지막 요소(7번 인덱스)를 저장
    int last_element = t[n][7];
    for (int i=7;i>0;i--)
        t[n][i] = t[n][i - 1];
    //저장했던 마지막 요소를 첫 번째로 이동
    t[n][0] = last_element;
    //회전 후 처리 표시
}

void rotate_counterclock(int n){
    //배열의 마지막 요소(7번 인덱스)를 저장
    int first_element = t[n][0];
    for (int i=0;i<7;i++)
        t[n][i] = t[n][i+1];
    //저장했던 마지막 요소를 첫 번째로 이동
    t[n][7] = first_element;
    //회전 후 처리 표시
}

void check_rotation(int start_idx, int start_dir) {
    //시작 톱니 방향 변경
    rotation_dir[start_idx] = start_dir;
    
    // 오른쪽 톱니바퀴 (start_idx -> 3까지) 전파 확인
    for (int i = start_idx; i < 3; ++i) {
        // 현재 톱니 (i)의 2번 톱니와 다음 톱니 (i+1)의 6번 톱니 극이 다르면 전파
        if (t[i][2] != t[i+1][6]) {
            rotation_dir[i+1] = -rotation_dir[i]; // 반대 방향 회전
        } else {
            break; // 극이 같으면 전파 중단
        }
    }
    // 왼쪽 톱니바퀴 (start_idx -> 0까지) 전파 확인
    for (int i = start_idx; i > 0; --i) {
        // 현재 톱니 (i)의 6번 톱니와 이전 톱니 (i-1)의 2번 톱니 극이 다르면 전파
        if (t[i][6] != t[i-1][2]) {
            rotation_dir[i-1] = -rotation_dir[i]; // 반대 방향 회전
        } else {
            break; // 극이 같으면 전파 중단
        }
    }
}

void apply_rotation() {
    for (int i = 0; i < 4; ++i) {
        if (rotation_dir[i] == 1) 
            // t[i] 배열을 시계방향으로 1칸 회전
            rotate_clock(i);
        else if (rotation_dir[i] == -1) 
            // t[i] 배열을 반시계방향으로 1칸 회전
            rotate_counterclock(i);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int ans=0;
    //톱니바퀴 초기화
    for(int i=0;i<4;i++)
        for(int j=0;j<8;j++) {
            char c;
            cin >> c;
            t[i][j] = c-'0';
        }
    cin>>k;
    while(k--){
        int idx,dir;
        cin >> idx>>dir;
        v.push_back({idx,dir});
    }
    
    for(auto c:v){
        int idx = c.first-1;
        int dir = c.second;
        //처리 톱니 초기화
        fill(rotation_dir,rotation_dir+4,0);
        check_rotation(idx,dir);
        apply_rotation();
    }
    
    for(int i=0;i<4;i++){
        int score = 1<<i;
        if(t[i][0]) ans+=score;
    }
    cout<<ans;
    return 0;
}