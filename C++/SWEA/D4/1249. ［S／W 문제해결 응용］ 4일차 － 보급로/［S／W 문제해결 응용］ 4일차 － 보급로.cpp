#include<bits/stdc++.h>
using  namespace std ;
int dx[4] = {-1,0,1,0};
int dy[4]  = {0,-1,0,1};

// 다익스트라  가장 작은 값이 위로 오게 
// 값, x,y 
using tiii = tuple<int,int,int>; 
int T;
int board [101][101];
int min_cost[101][101]; 
const int MIN_VAL = 1e9; 

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> T;
    for(int t=1;t<=T;t++){
        int n ;
        int val = 0;
        cin >> n;
        priority_queue<tiii, vector<tiii>,greater<tiii>> pq; 
        memset(board, 0 ,sizeof(board));
        // 2차원 배열을 1e9로 안전하게 채우는 방법
		fill(&min_cost[0][0], &min_cost[0][0] + 101 * 101, MIN_VAL);
        string s ;
        for(int i=0;i<n;i++)
        {	
            cin >> s; 
            for(int j=0;j<n;j++){
                board[i][j] =s[j] -'0';
            }
        }
            
        
        pq.push({0,0,0});
        min_cost[0][0] = 0; 
        cout<< '#'<< t << ' ' ;
        while(!pq.empty()){
        	auto [cost,x,y] = pq.top(); 
            pq.pop();
            if(x==n-1 && y==n-1) {
                cout<< cost <<'\n';
                 break;
           }
            if(cost > min_cost[x][y]) continue; 
            for(int dir = 0;dir<4;dir++){
            	int nx = x+dx[dir];
                int ny = y + dy[dir];
                if(nx<0|| ny< 0 || nx>=n || ny>= n ) continue; 
                int nxt_cost = cost +  board[nx][ny] ;
                if(nxt_cost< min_cost[nx][ny] ) { //적은 경우에만 업데이트 
                    min_cost[nx][ny] = nxt_cost ;
                    pq.push({nxt_cost, nx, ny}); 
                }
            }
        }
    }
	return 0 ;
}
