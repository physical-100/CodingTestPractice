#include <bits/stdc++.h>
using namespace std;

/*
r 연산 : 모든 행에 대해서 정렬 수행 
c 연산 : 모든 열에 대해 정렬 수행 
등장횟수를 저장 -> 숫자 크기  
 배열 A에 정렬된 결과 다시 입력 
 넣을 때는 수와 등장 횟수를 모두 넣의며 우선순위  수 

 배열에 넣을 때 행이나 열의 크기가 바뀜 
 r -> 가장 큰 행을 기준으로 모든 행의 크기가 변함 
 C -> 가장 큰 열을 기준으로 모든 열의 크기 변환 
 커진 곳은  0이 채워짐 => 수를 정렬할 때  0은 무시한다. 
 100을 넘어가는 경우 처음 100개를 제외한 나머지는 버림. 
 배열 A에 들어이있는 수와 r,c,k가 주어질때 A[r][c]에 들어 있는 값이 
 k가 되기 위한 최소 시간을 구하자.
*/
int r,c,k;
int board[100][100];
int R =3,C=3;
int t ;
void r_func(){
    int max_c = 0;
    for(int i=0;i<R;i++){
        vector<pair<int,int>> v;
        int check[101] = {0};
        for(int j=0; j<C;j++)
            //우선 값을 확인 
            if(board[i][j]) check[board[i][j]]++;
        for(int k=1;k<=100; k++)
            if(check[k]>0) v.push_back({check[k],k});
        sort(v.begin(),v.end());
        for(int j=0; j<C;j++) board[i][j]=0;
        int idx =0;
        for(auto p : v){
            if(idx>=100) break;
            board[i][idx++] = p.second;
            board[i][idx++] = p.first;
        }
        max_c = max(max_c,idx);
    }
    C = max_c;
}
void c_func() {
    int max_r = 0; 
    for (int i = 0; i < C; i++) { 
        
        vector<pair<int, int>> v;
        int check[101] = {0};
        for (int j = 0; j < R; j++) {
            if (board[j][i] == 0) continue;
            check[board[j][i]]++;
        }
        for (int k = 1; k <= 100; k++) {
            if (check[k] > 0) v.push_back({check[k], k});
        }
        sort(v.begin(), v.end());
        
        for (int j = 0; j < R; j++) board[j][i] = 0;

        // 5. 정렬된 결과를 i번째 열에 위에서 아래로(idx) 채우기
        int idx = 0;
        for (auto p : v) {
            if (idx >= 100) break;
            board[idx++][i] = p.second; // 값 (세로 방향 저장)
            board[idx++][i] = p.first;  // 개수 (세로 방향 저장)
        }
        max_r = max(max_r, idx); // 가장 길게 늘어난 열의 길이를 저장
    }
    R = max_r; // 전체 행(R) 크기 업데이트
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> r>>c>>k;
    for (int j=0; j<3; j++) 
        for(int i = 0;i<3;i++) 
            cin >> board[j][i];
    
    while(board[r-1][c-1]!=k && t <=100){
        if(R>=C) r_func();
        else c_func();
        t++;
    }

    if(t==101) cout <<-1;
    else cout << t;
    return 0;
}