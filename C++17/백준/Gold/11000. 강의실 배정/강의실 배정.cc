#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second
int n;
/*
s ->t에 끝나는 N개의 수업이 주어진다 
이때 최소의 강의실을 사용해서 모든 수업을 가능하게 해야함 
*/
// 각 강의실의 시작 종료 시간을 업데이트 
//가장 작은 게 앞으로 와야한다. 
//< et> 
priority_queue<int, vector<int>, greater<int>> pq;
int ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    vector<pair<int,int>> c(n);
    for(int i=0;i<n;i++){
        cin>> c[i].X >> c[i].Y;
    }
    sort(c.begin(),c.end());
    pq.push(c[0].Y);
    for(int i = 1; i < n; i++){
        //현재 강의 시작 시간보다 이전에 끝나는 강의가 있으면 거기 교실에 넣는다. 
        if(pq.top()<=c[i].X) pq.pop();
        pq.push(c[i].Y);
    }
    cout<< pq.size();
    return 0;
}