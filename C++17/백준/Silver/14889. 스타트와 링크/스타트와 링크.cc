#include <bits/stdc++.h>
using namespace std;
/*
모인 사람 N, => 짝수 
1~N 배정  -> 능력치 조사
스타트 팀과 링크 팀의 능력치 차이의 최솟값을 출력 


*/
int n;
int score[20][20];
int diff = 10e+6;
int comb[20];
//양 팀간의 차이를 구한다

int get_diff(vector<int> l, vector<int>s){
    int l_score=0;
    int s_score=0;
    for(auto r :l){
        for(auto c: l )
            l_score += score[r][c];
    }
   for(auto r :s){
        for(auto c: s )
            s_score += score[r][c];
    }
    return abs(l_score -s_score);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>> score[i][j];
    
    fill(comb+n/2,comb+n,1);
    do{
        vector<int> l, s;
        //comb에서 0이면  s, 1이면 l팀 
        for(int i=0;i<n;i++){
            if(comb[i])s.push_back(i);
            else l.push_back(i);
        }
        diff = min(diff,get_diff(l,s));
    }while(next_permutation(comb,comb+n));
    cout << diff;
    return 0;
}