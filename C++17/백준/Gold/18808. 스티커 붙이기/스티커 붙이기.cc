#include <bits/stdc++.h>
using namespace std;
/*
스티커를 붙이는 규칙 
1. 노트북에 붙일 수 있는 위치를 찾는다. 여러군데 위치할 수 있다면 가장 위쪽의 위치를 선택한다.
위에서도 여러군데 붙일 수 있다면 가장 왼쪽위치를 선택한다.
2. 붙일 수 있는 위치가 없다면 시계방향으로 90도 회전 후 다시 위치를 찾는다(1번 과정을 반복)
3. 360도가 될때까지 돌려보고 위치가 없으면 버린다.

노트북의 크기와 스티커가 주어졌을 때 스티커를 차례로 붙이고 난뒤 
노트북에서 몇개의 칸이 채워졌는지 출력

*/
int N,M,K;
int stickers[100][11][11];
vector<pair<int,int>> sticker_sz;
bool notebook[41][41]; //스티커를 붙일 노트북 표시

bool ispossible(int x, int y,int sticker){ //몇번째 스티커인지 같이 넘김
    //스티커의 영역과 노트북의 영역이 겹치는 부분이 있는지 확인하면 된다.
    for(int i=0;i<sticker_sz[sticker].first;i++){
        for(int j=0;j<sticker_sz[sticker].second;j++){
            if(notebook[x+i][y+j]==1&&stickers[sticker][i][j]==1) 
                return false;
        }
    }
    //겹치지 않을 때 sticker를 노트북에 붙이기
    for(int i=0;i<sticker_sz[sticker].first;i++){
        for(int j=0;j<sticker_sz[sticker].second;j++){
            if(stickers[sticker][i][j]==1) 
                notebook[x+i][y+j]=1;
        }
    }
    return true;
}

void rotate(int sticker) {
    int r = sticker_sz[sticker].first;
    int c = sticker_sz[sticker].second;
    int tmp[11][11];

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            tmp[i][j] = stickers[sticker][i][j];

    for (int i = 0; i < c; i++)
        for (int j = 0; j < r; j++)
            stickers[sticker][i][j] = tmp[r - 1 - j][i];

    sticker_sz[sticker] = {c, r}; // 크기 업데이트
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M>>K;
    for(int i=0;i<K;i++){
        int r,c;
        cin>>r>>c;
        sticker_sz.push_back({r,c});
        for(int j=0;j<r;j++)
            for(int e=0;e<c;e++) cin >> stickers[i][j][e];
    }
    
    for(int i=0; i<K; i++){
        bool is_paste = false;
        for(int dir=0; dir<4; dir++){
            int r = sticker_sz[i].first;
            int c = sticker_sz[i].second;
            for(int x=0; x<=N-r; x++){
                if(is_paste) break;
                for(int y=0; y<=M-c; y++){
                    if(ispossible(x,y,i)){
                        is_paste = true;
                        break;
                    }
                }
            }
            if(is_paste) break;
            rotate(i);
        }
    }
    //답 도출
    int cnt = 0;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            cnt += (int)notebook[i][j];
    cout << cnt <<'\n';
    
    
    return 0;
}