#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second

/*
회의실은 1개
N개의 회의에 대해 회의실 사용표 작성 
각 회의 시작시간 및 종료 시간 주어진다 
겹치지 않으면서 회의의 최대 개수를 찾자 
(시작 시간과 끝나는 시간이 같을 수도 있음 )
*/
int n,ans;
pair<int,int> meetings[100001];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
        int s,e;
        cin>>s>>e;
        meetings[i] = {s,e};
    }
    //그리디 -> st, et를 정해서 et까지 가는 중에 더 작은 et를 발견하면 et를 변환 
    //그전에 st을 기준으로 정렬 
    sort(meetings,meetings+n);
    //for(int i=0;i<n;i++) cout<<meetings[i].X<<' '<<meetings[i].Y<<'\n';
    int st=meetings[0].X;
    int et=meetings[0].Y;
    ans++;
    for(int i=1;i<n;i++){
        if(et<=meetings[i].X){
            //이전 회의가 끝난 경우 st 변경 
            st=meetings[i].X;
            et= meetings[i].Y;
            ans++;
            //cout <<"st: "<<st<<"et: "<<et<<'\n';
        }
        else if(et>meetings[i].Y){
            //이전 회의가 해당하는 시간에 더 빨리 끝나는 회의가 존재하는 경우
            et = meetings[i].Y;
            //cout <<"st: "<<st<<"et: "<<et<<'\n';
        }
        else continue;
    }

    cout<<ans;
    
    
    return 0;
}