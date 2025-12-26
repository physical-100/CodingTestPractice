#include <bits/stdc++.h>
using namespace std;
/*
시작점  
시작 방향 
세대를 가짐 
4 꼭지점이 모두 커브인 사각형의 개수를 구해라  
입력 드래곤 커브는 벗어나지 않으며 겹칠 수 있음 

규칙 :  n번째 세대는 n-1번째 세대의 값을 뒤에서 읽으면서 +1을 한 것과 같음 
+1? : 시계 방향 90도 회전
*/
int  N ;
int board[101][101];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,-1,0,1};
int t[20][4];
int cnt;

bool check(int r, int c){
    return (board[r][c] &&board[r][c+1] &&board[r+1][c] &&board[r+1][c+1] );
}
void make_dragon_C(int k){
    
    int g = t[k][3];
    //초기 d를 넣고 초기화 
    vector<int> v = {t[k][2]} ;
    //방향 리스트 완성 
    if(g!=0){
         for(int i=1; i<=g;i++){
             int sz = v.size();
             for(int j=sz-1;j>=0 ; j--){
                 v.push_back((v[j]+1)%4);
             }
         }
    }
    
    int nx = t[k][0];
    int ny = t[k][1];
    board[nx][ny]++;
    for(auto dir:v){
        nx  = nx+dx[dir];
        ny = ny + dy[dir];
        board[nx][ny]++;
    }

    
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    for(int i=0;i<N;i++) {
          for(int j=0;j<4 ; j++) cin >> t[i][j];
    }
    for(int i = 0; i<N;i++){
        make_dragon_C (i);
    }
    for(int i=0;i<100;i++) {
        for(int j=0;j<100 ; j++) {
         if(check(i,j)) cnt++;     
        }
    }
    cout << cnt ; 
    
    return 0;
}