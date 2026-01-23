#include <bits/stdc++.h>
using namespace std;
/*
방향 없는 그래프가 있을 때 연결 요소의 개수를 구하라 
*/
int N,M;
vector<int> v1[1001];
int visited[1001];
int ans;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> N>>M;
    for(int i=0;i<M;i++){
        int u,v;
        cin>> u>>v;
        v1[u].push_back(v);
        v1[v].push_back(u);
    }
    for(int i=1;i<=N;i++){
        if(visited[i]) continue;
        ans++;
        queue<int> q;
        q.push(i);
        visited[i]=1;
        while(!q.empty()){
            auto cur = q.front(); q.pop();
            for(auto c: v1[cur]){
                if(visited[c]) continue;
                q.push(c);
                visited[c]=1;
            }
        }
    }
    cout << ans;
    return 0;
}