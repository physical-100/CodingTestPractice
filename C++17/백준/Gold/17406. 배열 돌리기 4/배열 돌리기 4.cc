#include <bits/stdc++.h>
using namespace std;
int N,M,K;
int board[50][50];
vector<tuple<int,int,int>> rotations;
/*
 배열의 값 -> 각 행의 합 중 최솟값 
*/
int mx = 1e9;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N>>M>>K;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++) cin>>board[i][j];
    vector<int> b; 
    for(int i=0;i<K;i++){
        int r,c,s;
        cin>> r>>c>>s;
        rotations.push_back({r,c,s});
        b.push_back(i);
    }
    
    do{
        int tmp[50][50];
        memcpy(tmp,board,sizeof(board));
        for(auto idx: b){
            auto [r,c,s ] = rotations[idx];
            int c_r = r-1;
            int c_c = c-1;
        
            for(int i=1;i<=s ; i++){
                int top = c_r -i ;
                int bot =  c_r +i;
                int left = c_c -i;
                int right = c_c+ i;
                int last  = tmp[top][left];
                
                //회전은 중심을 기준으로 테두리 별로 한 칸씩 밀기  
                for(int j=top;j<bot;j++) tmp[j][left] = tmp[j+1][left];
                for(int j=left;j<right;j++) tmp[bot][j] = tmp[bot][j+1];
                for(int j=bot;j>top;j--) tmp[j][right] = tmp[j-1][right];
                for(int j=right;j>left+1;j--) tmp[top][j] = tmp[top][j-1];
                tmp[top][left+1] = last; 
            }
        }

        //최솟값 
        for(int i=0;i<N;i++)
            mx= min(mx,accumulate(tmp[i],tmp[i]+M,0));
    }while(next_permutation(b.begin(),b.end()));
    cout << mx; 
    return 0;
}