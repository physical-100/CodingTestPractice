#include <bits/stdc++.h>
using namespace std;
/* 7명이 되어야 함-> 이다솜 파가 더 많아야한다. 
    5X5의 격자
    적어도 4명 이상.
*/

char c[5][5];
bool combination[25];
int dx[4] = {1,0,-1,0};
int dy[4] = {0,-1,0,1};
int possible ; 


int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)cin>> c[i][j];
    //25개 중 중복 없이 7개를 뽑아내기 위해 앞 7개를 0으로 세팅
    fill(combination+7,combination+25,1);
    do{
        int princess=0,s_num=0;
        queue<pair<int,int>> q;
        bool is7p[5][5]={};
        bool visited[5][5] = {};
        for(int i=0;i<25;i++){
            if(!combination[i]){
                int x = i/5,y=i%5;
                is7p[x][y]=1;
                if(q.empty()){
                    q.push({x,y});
                    visited[x][y]=1;
                }
            }
        }
        while(!q.empty()){
            auto cur = q.front();
            if(c[cur.first][cur.second]=='S') s_num++;
            princess++;
            q.pop();
            for(int dir=0;dir<4;dir++){
                int nx = cur.first + dx[dir];
                int ny = cur.second + dy[dir];
                if(nx<0||ny<0||nx>=5||ny>=5) continue;
                if(visited[nx][ny])continue;
                if(!is7p[nx][ny]) continue;
                q.push({nx,ny});
                visited[nx][ny]=1;
            }
        }
        if(princess>=7&&s_num>=4) possible++;
    }while(next_permutation(combination,combination+25));

    cout << possible;
    return 0;
}