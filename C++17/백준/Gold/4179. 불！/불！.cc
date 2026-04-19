#include<bits/stdc++.h>
using namespace std;

string s[1002];

int R,C;
int dx[4] = {1,0,-1,0};
int dy[4]= {0,-1,0,1};
// 다 0으로 채우기
int f_dist[1002][1002];//불 전파 시간  
int j_dist[1002][1002];//지훈 이동 시간

// #: 벽 . : 지나갈 수 있는 공간, J: 지훈 위치 , F: 불이 난 공간

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> R>>C;

    for(int i = 0; i < R; i++){
        fill(f_dist[i], f_dist[i]+C, -1);
        fill(j_dist[i], j_dist[i]+C, -1);    
      }
    
    for(int i=0 ; i<R;i++) cin >> s[i];

    queue<pair<int,int>> Qj; //지훈이 갈 곳
    queue<pair<int,int>> Qf; // 불 위치 -> 근데 불은 번지는데 지훈 위치는 바뀌는건데 흠.
    
    for(int i=0; i<R;i++ ){
        for (int j=0;j<C; j++){
            if(s[i][j]=='J') {
                j_dist[i][j]=0;
                Qj.push({i,j});
            }
            else if(s[i][j]=='F') {
                f_dist[i][j]=0;
                Qf.push({i,j});
            }
        }
    }
    
    while(!Qf.empty()){
        auto cur = Qf.front();
        Qf.pop();
        
        for(int dir=0; dir <4 ; dir++){
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if (nx>=R||nx<0 ||ny>=C||ny<0)continue;
            if (s[nx][ny]=='#'||f_dist[nx][ny]>=0) continue;
            
            f_dist[nx][ny] = f_dist[cur.first][cur.second]+1;
            Qf.push({nx,ny});
        }
    }
    while(!Qj.empty()){
        auto cur = Qj.front();
        Qj.pop();
        for(int dir=0; dir <4 ; dir++){
            int nx = cur.first + dx[dir];
            int ny = cur.second + dy[dir];
            if (nx>=R||nx<0 ||ny>=C||ny<0){ //범위를 벗어난 것은 탈출에 성공했다는 의미
                cout<<j_dist[cur.first][cur.second]+1;
                return 0;
            }
            if (s[nx][ny]=='#'|| j_dist[nx][ny]>=0) continue;
            if(f_dist[nx][ny]!=-1 && j_dist[cur.first][cur.second]+1>=f_dist[nx][ny])continue;
            j_dist[nx][ny] = j_dist[cur.first][cur.second]+1;
            Qj.push({nx,ny});
        }
    }
    cout<<"IMPOSSIBLE";
}