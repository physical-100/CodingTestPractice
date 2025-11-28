#include <bits/stdc++.h>
using namespace std;

int n;
vector<pair<int,int>> v[2]; //black ,  white를 각각 저장
int black_max , white_max;
bool isused[2][22]; //대각선 방향별로 저장 => black의 값과 white의 값이 달라 하나로 해도 됨

void bishop(int color , int idx ,int &max_val ,int cnt){
    if(idx==v[color].size()){
        max_val = max(max_val,cnt);
        return;
    }
    int s = v[color][idx].first + v[color][idx].second; //합
    int d = v[color][idx].first - v[color][idx].second + 10 ;// offset을 통해 차의 부호 분리

    if(!isused[0][s] && !isused[1][d]){ // 비숍을 놓는 경우
        isused[0][s] =1;
        isused[1][d] =1;
        bishop(color,idx+1,max_val,cnt+1);
        isused[0][s]=0;
        isused[1][d]=0;
    }
    bishop(color,idx+1,max_val,cnt); // 그냥 놓지 않는 경우.
    
        
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    int d;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> d;
            if(d) {
                if((i+j)%2==0)v[0].push_back({i,j});
                else v[1].push_back({i,j});
            }
        }
    }
    bishop(0,0,black_max,0);
    bishop(1,0,white_max,0);

    cout << black_max+white_max;
        
    return 0;
}