#include <bits/stdc++.h>
using namespace std;
/*
정사각형을 여러개 이어서 붙인 도형  : 폴리오미노 
도형은 모두 연결되어 있어야함 
정사각형 4개를 이어서 붙인 폴리오미노 =>> 테트로미노 
크기가 NxM인 종이 위에 테트로 미노를 하나 놓음 
테트로 미노가 놓인 칸에 쓰여있는 수들의 합을 최대로 하는 프로그램
가능한 테트로 미노 ->  5개  
*/

int N,M;
int board[500][500];
bool isselected[500][500];
int ans;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};


int selected[4];
bool check(int x,int y){
    return (x>=0&&x<N&&y>=0&&y<M);
}
void T_func(int x,int y){
    int comb[4] ={0,1,1,1};
    // 4방향에서 3방향을 고르는 조합 
    
    do{
        vector<int> T_select ; 
        T_select.push_back(board[x][y]);
        for(int dir=0;dir<4;dir++){
            if(comb[dir]){ //1이면 선택된 방향 
                if(!check(x+dx[dir],y+dy[dir])) break; 
                T_select.push_back(board[x+dx[dir]][y+dy[dir]]);
            }
        }
        if(T_select.size()==4) 
            ans = max(ans,accumulate(T_select.begin(),T_select.end(),0));
        
    }while(next_permutation(comb,comb+4));
}
void func(int k,int x,int y){
    if(k ==4){
      // 4개가 되면 합을 구함
        ans = max(ans,accumulate(selected,selected+4,0));
        return ; 
    } 
    isselected[x][y]=1 ;
    // 아 문제 발생 ㅗ 이 모양을 못찾아내네..  => 별도로 구현하자.
    for(int dir=0; dir<4;dir++){
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if(!check(nx,ny)) continue;
        if(isselected[nx][ny]) continue;
        //isselected[nx][ny]=1;
        selected[k] = board[nx][ny];
        func(k+1 ,nx,ny);
    }
    
    isselected[x][y]=0;    
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N>>M;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++) cin>> board[i][j];
    
     for(int i=0;i<N;i++)
        for(int j=0;j<M;j++) {
            func(0,i,j);
            T_func(i,j);
        }
    
    cout << ans;
    return 0;
}