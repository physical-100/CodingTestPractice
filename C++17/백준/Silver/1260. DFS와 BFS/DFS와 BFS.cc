#include <bits/stdc++.h>
using namespace std;

int N, M, V;
 bool visited[10001];
vector<int> v[10001];
void DFS(int k){
    cout<< k <<' ';
    visited[k]=1;
    sort(v[k].begin(),v[k].end());
    for(auto cur:v[k]){
        if(visited[cur]) continue;
        DFS(cur);
    }
    
}
void BFS(){
    memset(visited,0,sizeof(visited));
    queue<int> q;
    q.push(V);
    visited[V]=1;
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        cout<< cur <<" ";
        sort(v[cur].begin(),v[cur].end());
        for(auto c:v[cur]){
            if(visited[c]) continue;
            q.push(c);
            visited[c]=1;
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M>>V;
    while(M--){
        int a,b;
        cin >> a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    DFS(V);
    cout <<'\n';
    BFS();
    
    return 0;
}