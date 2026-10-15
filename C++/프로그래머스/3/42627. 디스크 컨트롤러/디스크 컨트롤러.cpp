#include<bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int> tii;
int solution(vector<vector<int>> jobs) {
    int answer = 0;
    int sz = jobs.size();
    //처리시간,요청 시각,작업 번호 
    vector<tii> v;
    for(int i=0;i<sz;i++) v.push_back({jobs[i][0],jobs[i][1],i});
    sort(v.begin(), v.end());
    
    priority_queue<tii, vector<tii>, greater<tii>> pq;
    //요청 시각이 가장 빠른 것 부터 넣음 
    //우선 순위 큐에 저장
    int time = 0,idx=0;
    while(idx<sz||!pq.empty()){
        // if(pq.empty()) continue;
        //시간이 되면 요청을 넣는다.
        while(idx<sz&&get<0>(v[idx])<=time){
            pq.push({get<1>(v[idx]),get<0>(v[idx]),get<2>(v[idx])});
            idx++;
        }
        if(!pq.empty()){
              //요청 넣고 가장 상위 꺼 수행 
            auto [p_t, c_t, i]  = pq.top();
            pq.pop();
            time += p_t;
            answer+= (time - c_t);
        }
        else time = get<0>(v[idx]); 
        }
    return answer/sz;
}