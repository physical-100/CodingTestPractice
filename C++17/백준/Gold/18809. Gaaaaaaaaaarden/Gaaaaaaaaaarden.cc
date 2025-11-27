#include <bits/stdc++.h>
using namespace std;
/*
너비우선 탐색 
브루트포스 
시뮬레이션 
백트래킹인가?
모든 경우의 수를 확인한다.
가능한 땅의 수 , 초록, 빨강의 색을 채운다..
땅의 수는 10개 이하라 모두 가능할 듯.
0: 호수  1: 배양액을 뿌릴 수 없는 땅 2: 배양액을 뿌릴 수 있는 땅 
동시에 도달하면 꽃이 생긴다 꽃이 생기면 더 이상 퍼져나가지 않음.
*/
int dx[4] = {1,0,-1,0};
int dy[4] = {0,-1,0,1};
int N,M,G,R;
int board[52][52];
int mx_flower;
const int Red=1;
const int Green = 2;
const int Flower = 99;
vector<pair<int,int>> possible_land;
int possible_case[10]; //가능한 땅에서 조합을 저장할 배열
int land_SZ ;

void func(){
    int cnt=0;
    pair<int,int> state[51][51]; //퍼져 나가는 시간을 저장할 배열 <시간,색>
    queue<pair<int,int>> q; //BFS용 큐
    for(int i=0;i<land_SZ;i++){
        //상태를 초기화 하고
        if(possible_case[i]==Red||possible_case[i]==Green){
            state[possible_land[i].first][possible_land[i].second] = {0,possible_case[i]};
            q.push(possible_land[i]);
        }  
    }
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        int cur_t = state[cur.first][cur.second].first;
        int cur_c = state[cur.first][cur.second].second;
        //꽃이면 패스
        if(state[cur.first][cur.second].second==Flower) continue;
        
        for(int dir=0; dir<4;dir++){
            int nx = cur.first +  dx[dir];
            int ny = cur.second +  dy[dir];
            
            if(nx<0||ny<0||nx>=N||ny>= M)continue;
            if(board[nx][ny]==0) continue;
            
            if(state[nx][ny].second == 0){
                state[nx][ny] = {cur_t+1,cur_c};
                q.push({nx,ny});
            }
             else if(state[nx][ny].second == Red){
                if(cur_c == Green && state[nx][ny].first == cur_t+1){
                  cnt++;
                  state[nx][ny].second = Flower;
                }
              }
          else if(state[nx][ny].second == Green){
            if(cur_c == Red && state[nx][ny].first == cur_t+1){
                cnt++;
                state[nx][ny].second = Flower;
            } 
          }
        }
    }
    mx_flower=max(cnt,mx_flower);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M>>G>>R;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin >> board[i][j];
            if(board[i][j]==2) possible_land.push_back({i,j});
        }
    }
    land_SZ = possible_land.size();
    fill(possible_case+land_SZ-G-R,possible_case+land_SZ-G,Red);
    fill(possible_case+land_SZ-G,possible_case+land_SZ,Green);
    do{
        func();
    }while(next_permutation(possible_case,possible_case+land_SZ));

    cout <<mx_flower;
    return 0;
}