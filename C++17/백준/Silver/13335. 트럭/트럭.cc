#include <bits/stdc++.h>
using namespace std;
/*
하나의 차선으로 된 다리  n개의 트럭이 건넌다 
조건 : 
    1. 트럭의 순서는 바꿀 수 없다
    2. 트럭의 무게는 다르거나 같다. 
    3. 다리 위에는 w대의 트럭만 동시에 올라갈 수 있다.
    4. 각 트럭은 단위 시간에 하나의 단위 길이 만큼만 이동한다 가정
    5. 다리 위의 트럭의 무게의 합은 다리의 최대 하중 L보다 작거나 같아야 함.

다리에 걸친 트럭의 무게는 제외 

모든 트럭이 다리를 건너는 최단 시간을 구하라 

큐를 활용하자
*/

int  n,w,L;
queue<int> wait_truck ;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> w >> L;
    int weight;
    deque<int>bridge_q(w,0);
    while(n--) {
        cin >> weight;
        wait_truck.push(weight);
    }
    
    int cur_weight =0,time = 0;
    //대기 큐가 차있거나 현재 다리 위의 차량이 있는 경우 반복
    while(!wait_truck.empty()||cur_weight >0){
        time++;
        
        int out_weight = bridge_q.front(); 
        bridge_q.pop_front();
        cur_weight -= out_weight; // 빠져나가는 만큼 값이 빠짐.
        
        if(!wait_truck.empty()){
            //다음의 트럭 무게 
            int nxt_weight = wait_truck.front();
            if(cur_weight+nxt_weight<= L){
                wait_truck.pop();
                cur_weight += nxt_weight;
                bridge_q.push_back(nxt_weight);
                
            }else bridge_q.push_back(0);
            
        }else bridge_q.push_back(0);
    }
    cout <<time;
    return 0;
}