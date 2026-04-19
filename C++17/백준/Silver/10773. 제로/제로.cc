#include<bits/stdc++.h>
using namespace std;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int K, s=0;
    stack<int> S;
    cin >> K;
    while(K--){
        int n;
        cin >> n;
        if(n==0)S.pop();
        else S.push(n);
    }
    while(!S.empty()){
        s+=S.top();
        S.pop();
    }
    cout << s;
}