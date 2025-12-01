#include <bits/stdc++.h>
using namespace std;
/*
4개 이상 상하좌우로 연결되어 있으면 연결된 같은 색 뿌요가 사라짐
이후에 위에 있던 뿌요들은 내려옴 => 테트리스
터질때마다 1연쇄가 증가 
터질 수 있는 뿌요가 여러 그룹이 있다면 동시에 터짐 -> 이때도 1연쇄 증가
*/
int dx[4]= {1,0,-1,0};
int dy [4]= {0,-1,0,1};
int cnt;
char fields[12][6];
bool is_visited[12][6];
bool flag; //연쇄가 되는지 확인하는 변수


bool isbreak(){
    //is_visited 초기화
    for(int i=0;i<12;i++) fill(is_visited[i],is_visited[i]+6,0);
    
    queue<pair<int,int>> q;//큐를 담을 공간
    
    vector<pair<int,int>> v; // 연쇄적으로 부서질 좌표를 담을 벡터
    
     for(int i=0;i<12;i++){
        for(int j=0;j<6;j++){
            if(is_visited[i][j]) continue;
            if(fields[i][j]=='.'){ 
                is_visited[i][j]=1;
                continue;
            }
            vector<pair<int,int>> v_tmp;
            char cur_c = fields[i][j]; //현재 색깔
            v_tmp.push_back({i,j});
            is_visited[i][j]=1;//방문했다고 표시.
            
            q.push({i,j});
            while(!q.empty()){
                auto cur = q.front(); q.pop();
                for(int dir=0;dir<4;dir++){
                    int nx = cur.first +  dx[dir];
                    int ny = cur.second +  dy[dir];
                    if(nx<0||ny<0||nx>=12||ny>=6) continue;
                    //같은 색만 큐에 추가 
                    if(fields[nx][ny]==cur_c && !is_visited[nx][ny]){
                        q.push({nx,ny});
                        is_visited[nx][ny]=1;
                        v_tmp.push_back({nx,ny});
                    }
                }
            }
            //4개 이상이면 값 추가
            if(v_tmp.size()>=4){ 
                for(auto c: v_tmp) v.push_back(c);
            }
        }
    }
    //v안의 좌표를 모두 0으로 변경
    for(auto c:v) fields[c.first][c.second]='.';
    if(v.size()>0) return true;
    else return false;
}

void update(){
    //각 col을 아래에서부터 확인
    for(int col=0; col<6; col++){
        int empty_row = 11;
        for(int row=11; row>=0; row--){
            if(fields[row][col] != '.'){
                //.이 아니면 해당 값을 변경하고 empty_row를 -1해서 목표 위치를 수정
                swap(fields[row][col], fields[empty_row][col]);
                empty_row--;
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    //fields 초기화
    for(int i=0;i<12;i++)
        for(int j=0;j<6;j++)cin >> fields[i][j];
    flag = isbreak();
    
    while(flag){
        update();
        cnt++;
        flag = isbreak();
    }
    cout<<cnt;
    return 0;
}