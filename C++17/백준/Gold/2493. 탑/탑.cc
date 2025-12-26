#include<bits/stdc++.h>
using namespace std;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N ;
    cin >> N;
    stack<int> s;
    vector<int> height(N+1);
    for (int i = 1 ;i<N+1;i++) cin >>height[i];
    vector<int> ans(N+1,0); //0으로 채운다.

    for (int i = 1; i<N+1;i++){
        while(!s.empty()&&height[s.top()]<=height[i]){
            s.pop();
        }
        if(!s.empty()){
            ans[i] = s.top();
        }
        s.push(i);
    }
    for (int i = 1 ;i<N+1;i++) cout << ans[i] <<" ";
}