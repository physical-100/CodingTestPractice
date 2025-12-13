#include <bits/stdc++.h>
using namespace std;
/*
새로 세울 수 있는 벽은 3개[무조건 3개를 세워야한다]
바이러스는 상하좌우 인접한 칸으로 퍼져나갈 수 있음 
0: 빈칸  1: 벽 2: 바이러스
벽을 세우지 않으면 바이러스는 모든 빈칸으로 퍼질 수 있다 .
연구소의 지도가 있을 때 얻을 수 있는 안전 영역의 크기의 최댓값을 구하자. 

방법: 벽을 세울 수 있는 조합을 구해서 가능한 방법을 구한다.  

*/
int dx[4] = {1,0,-1,0};
int dy[4] = {0,-1,0,1};
int possible[64]; // 조합을 만들기 위해서 채움 . 

int board[9][9];
int N,M;
int cnt ; 
vector<pair<int,int>> virus;
vector<pair<int,int>> wall_possible;

int get_Area(int area[9][9], vector<pair<int,int>>v){
    int tmp = 0;
    bool isvisited[9][9];
    memset(isvisited, 0, sizeof(isvisited));
    queue<pair<int,int>> q;
    for(auto c: v){
        //임시 벽 생성 -> area는 복사본 아 배열은 포인터로 넘어가서 원본이 바뀐다.!
        
        area[c.first][c.second] = 1;
    }
    //큐에 바이러스 (시작 위치 집어 넣기)
    for(auto c: virus){
        q.push(c);
        isvisited[c.first][c.second]=1;
    }
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(int dir=0;dir<4 ; dir++){
            int nx =  cur.first +  dx[dir];
            int ny = cur.second +  dy[dir];
            if(nx<0||ny<0|| nx>=N||ny>=M) continue;
            if(area[nx][ny]!=0 || isvisited[nx][ny]) continue;
            q.push({nx,ny});
            area[nx][ny]=1;
            isvisited[nx][ny]=1;
        }
    }
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            if(area[i][j]==0) tmp++;

    return tmp;
    
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >>  N>> M; 
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin>>board[i][j];
            if(board[i][j]==2){
                virus.push_back({i,j});
            }
            else if(board[i][j]==0){
                wall_possible.push_back({i,j});
            }
        }
    }
    int wall_sz = wall_possible.size();
    //cout<< wall_sz;
    fill(possible+wall_sz-3,possible+wall_sz,1);
    //벽을 놓을 수 있는 영역의 수에서 가장 뒷자리 3개를 1로 변경 -> for permutation
    do{
        int area[9][9];
        memcpy(area,board, sizeof(area));
        vector<pair<int,int>> wall_3;
        for(int i=0;i<wall_sz;i++)
            if(possible[i]==1) {
                auto c = wall_possible[i];
                wall_3.push_back(c);
            }
        cnt = max(cnt,get_Area(area,wall_3));
        
    }while(next_permutation(possible,possible+wall_sz));
    cout << cnt;
    return 0;
}