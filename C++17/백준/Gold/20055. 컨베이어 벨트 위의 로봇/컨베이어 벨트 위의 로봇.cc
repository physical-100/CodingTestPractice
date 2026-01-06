#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second 
/*
1에서 올리기 
N에서 내리기 
로봇은 1~n-1 사이에서 스스로 이동 가능  
-> 로봇이 칸 위에 올라오면 칸의 내구도 감소 -1 

순서 
    1. 벨트가  칸 위의 로봇과 함께 한칸 회전 
    2. 가장 먼저 올라간 로봇 부터 회전하는 방향으로 한칸 이동할 수 있으면 이동 
        A. 이동 못하면 가만히 
        b. 이동 하기 위해서는 이동하려는 칸에 로봇이 없으며 칸의 내구도 1 이상 
    3. 올리는 위치의 칸의 내구도 0이 아니면 올리는 위치에 로봇을 올린다 .
    4. 내구도가 0인 칸의 개수가 K개 이상이라면 과정 종료 
        k개 이하면 다시 반복 
*/

int N,K;  // 벨트 길이 ->2N   K : 내구도 0인 개수 최대 
deque<pair<int,int>> belts; //내구도  

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N>> K ;
    int durability ;
    for(int i =0;i<2*N ; i++) {
        cin >> durability;
        belts.push_back({0,durability});  // {로봇이 있는지. 내구도}
    }
    int stage = 0 , broken_belt = 0;
    while(broken_belt<K){
        stage ++;
        //벨트 회전 
        belts.push_front(belts.back());
        belts.pop_back();
        //내리는 위치  로봇 있으면 내림 
        belts[N-1].X = 0;
        // 로봇 이동 
        for(int i = N-2 ; i>=0 ; i--){
            if (belts[i].X && !belts[i + 1].X && belts[i + 1].Y > 0) {
                belts[i].X = 0;
                belts[i + 1].X = 1;
                belts[i + 1].Y--;
                
                // 이동 후 내리는 위치면 즉시 내림
                if (i + 1 == N - 1) belts[i + 1].X = 0;
                if(!belts[i+1].Y) broken_belt ++;
            }
        }
        //로봇 올리기 
        if(belts[0].Y >0){
            belts[0].X = 1;
            if(--belts[0].Y==0) broken_belt++;
        }
    }
    cout << stage ;
    return 0;
}