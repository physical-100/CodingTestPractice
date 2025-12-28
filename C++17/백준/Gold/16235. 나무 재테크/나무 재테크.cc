#include <bits/stdc++.h>
using namespace std;

/*
- 봄
    나무는 자신의 나이만큼 양분을 먹고 나이가 +1된다 
    한 땅에 여러개의 나무가 있는 경우 가장 나이가 어린 나무부터 양분을 먹는다 .  
    자신의 나이만큼 양분을 먹을 수 없는 나무는 즉시 죽는다 . 
- 여름 
    봄에 죽은 나무가 양분으로 변한다.
    죽은 나무의 나이를 2로 나눈값이 해당 칸으 양분으로 추가된다.(몫 연산 )
- 가을 
    나무 번식 => 나이가 5의 배수 
    인접한 8개의 칸에 나이가 1인 나무가 생성 된다 . 
- 겨울 양분 추가[ 입력으로 주어지는 만큼의 양분 추가 ]

=> K년이 지난 후 땅에 살아있는 나무의 개수를 구한다. 
*/

int n, m, k;  // n: 영토 크기  ,m : 초기 심는 나무 개수 , k : 지켜볼 시간  

int board[12][12];     // 현재 양분
int add_land[12][12];  // 겨울에 추가할 양분

// 각 칸에 있는 나무들의 나이(항상 오름차순 유지)
vector<int> trees[12][12];

// 8방향
int dx[8] = {-1,-1,-1, 0,0, 1,1,1};
int dy[8] = {-1, 0, 1,-1,1,-1,0,1};

void spring_summer(){  
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            auto &v = trees[i][j];
            int idx = (int)v.size()-1;
            for(;idx>=0;idx--){
                if(board[i][j]< v[idx]) break;
                board[i][j]-= v[idx]; //양분 흡수 
                v[idx] ++; // 나이 증가
            }
            //여름 
            //양분 이상의 2로 나눈 값을 추가 
            for(int s=0;s<=idx; s++) board[i][j]+= v[s]/2;
            
            v.erase(v.begin(),v.begin()+idx+1); //총 개수는 idx+1이다 
        }
    }
}

void fall_winter(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            //가을 
            for(auto age :  trees[i][j]){
                if(age%5==0){
                    for(int d=0;d<8;d++){
                        //범위 외도 그냥 추가 
                        trees[i+dx[d]][j+dy[d]].push_back(1);
                    }
                }
            }
            //겨울
            board[i][j]+= add_land[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    // 겨울에 추가될 양분 입력 && 초기 양분 초기화 
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j){
            cin >> add_land[i][j];
            board[i][j]=5;
        }

    // 초기 나무 입력
    while(m--){
        int x, y, age;
        cin >> x >> y >> age;
        trees[x][y].push_back(age);
    }

    // K년 시뮬레이션
    while (k--) {
                spring_summer();
                fall_winter();
    }
     
    // 살아있는 나무 수 집계
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            ans += trees[i][j].size();

    cout << ans ;
    return 0;
}
