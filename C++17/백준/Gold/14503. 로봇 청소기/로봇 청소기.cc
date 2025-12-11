#include <bits/stdc++.h>
using namespace std;
/*
청소기 바라보는 방향 존재 
현재 칸이 청소 되지 않은 경우 청소 
주변 4칸 확인  청소 칸이 없으면 
    한칸 후진
    불가능하다면 작동을 멈춘다.
청소가 가능한 경우 
    반시계 방향으로 90도 회전
    청소되지 않으면 한칸 전진
    d 0 :N 1: E 2:S 3: w
*/
int board[50][50];
bool isvisited[50][50];
int N,M;
int cur_x,cur_y,d;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int cnt;

void change_Direction(){
    d = (d-1>=0) ? d-1:3;
}
bool check_go(){
    for(int dir =0 ; dir<4 ;dir++){
        int nx = cur_x + dx[dir];
        int ny = cur_y + dy[dir];
        if (nx<0||ny<0||nx>=N||ny>=M)  continue;
        if(board[nx][ny]!=0|| isvisited[nx][ny]) continue;
        return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> N>>M;
    cin >> cur_x >>cur_y>>d;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++) cin >> board[i][j];
    bool stop = false;
    //queue<pair<int,int> q;
    //q.push({cur_x,cur_y});
    isvisited[cur_x][cur_y]=1;
    cnt++;
    while(!stop){
        if(check_go()){
            int n = 4;
            cnt++;
            while(n--){
                d = (d-1>=0)? d-1:3;
                int nx = cur_x + dx[d];
                int ny = cur_y + dy[d];
                //갈 수 있다. 
                if(!board[nx][ny]&&!isvisited[nx][ny]){
                    isvisited[nx][ny]=1;
                    cur_x = nx;
                    cur_y = ny;
                    break;
                }
            }
        }
        else{
            // 못 가는 경우 뒤로 이동
            int nd =  (d+2)%4;
            cur_x += dx[nd];
            cur_y += dy[nd];
            if(board[cur_x][cur_y]) stop=true;
        }
    }
    cout << cnt;
    
    return 0;
}