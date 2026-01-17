#include <bits/stdc++.h>
using namespace std ;
/*
    구역을 두개의 선거구로 나눈다 . 
    선거구는 최소 하나 
    인구 차이의 최솟값을 구하자.
    구역은 연결되어 있어야 한다 .
*/
int N ; 
int p[11]; // 각 구역의 인구 
vector<int> near[11] ;
const int impossible = 1e9;
int ans = impossible;

bool selected[11] ; 

bool isConnected(const vector<int>& group, bool type) {
    if (group.empty()) return false;

    queue<int> q;
    vector<bool> visited(N + 1, false); // 전체 구역 방문 여부
    
    q.push(group[0]);
    visited[group[0]] = true;
    int count = 1; // 방문한 구역 수

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (int nxt : near[cur]) {
            // 아직 방문 안 했고 + 같은 그룹(selected[nxt] == type)인 경우만 이동
            if (!visited[nxt] && selected[nxt] == type) {
                visited[nxt] = true;
                q.push(nxt);
                count++;
            }
        }
    }
    // 실제로 방문한 구역 수와 그룹의 크기가 같으면 연결된 것!
    return count == group.size();
}
void func(int k){
    if(k==N){
        //두 그룹 생성 
        vector<int> A,B;
        for(int i=0;i<N;i++){
            if(selected[i])
                A.push_back(i);
            else B.push_back(i);
        }
        if(!isConnected(A,1) || !isConnected(B,0)) return ;
        //모두 해당하면 각 지점의 인구수 계산
        int num_A =0,num_B =0;
        for(auto a: A)num_A += p[a];
        for(auto b : B) num_B += p[b];
        int tmp_val = abs(num_A-num_B);
        ans= min(ans , tmp_val);

        return ; 
    }
    selected[k] = true;
    func(k+1);
    selected[k] = false; 
    func(k+1);
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i=0;i<N;i++) cin>> p[i] ; 
    for(int i=0;i<N;i++) {
        int k;
        cin>> k;
        while(k--){
            int n;
            cin>> n;
            near[i].push_back(n-1);
        }
    }
    func(0);
    if(ans == impossible)
        cout << -1;
    else cout << ans;
    return 0;
}