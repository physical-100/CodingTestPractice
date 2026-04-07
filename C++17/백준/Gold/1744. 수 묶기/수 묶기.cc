#include <bits/stdc++.h>
using namespace std;

/*
길이가 N인 수열이 주어졌을 때 수열의 합을 구하려고 한다. 수열의 두수를 묶으려고 할때 위치에 상관없이 묶을 수 있음  
묶게되면 묶은 수는 서로 곱한 후에 더함 
수열의 모든 수는 한번만 묶거나 묶지 않아야한다 .
각 수를 적절히 묶어 합이 최대가 되게 하는 프로그램 작성 
*/
int n;
int arr[50];
int ans; 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    bool zero = false;
    priority_queue<int ,vector<int>,greater<int>> n_arr;  //가장 작은 값이 위로 오도록 설정 
    priority_queue<int>p_arr; //가장 큰 값이 위로 오도록 설정
    for(int i=0;i<n;i++) {
        cin>> arr[i];
        if(arr[i]<0) n_arr.push(arr[i]);
        else if(arr[i]>0)p_arr.push(arr[i]);
        else zero = 1; //0이 있는 경우 
    }
    //각 음수 양수 값을 바탕으로 더한다. 
    while(n_arr.size()>1){
        //1보다 크다면 진행 
        int a = n_arr.top(); n_arr.pop();
        int b = n_arr.top(); n_arr.pop();
        ans += a*b;
        
    }
    while(p_arr.size()>1){
        //1보다 크다면 진행 
        int a = p_arr.top(); p_arr.pop();
        int b = p_arr.top(); p_arr.pop();
        if(a==1||b==1) {
            ans +=a;
            ans+=b;
        }
        else ans += a*b;
    }
    if(!n_arr.empty()&&!zero) ans+= n_arr.top();
    if(!p_arr.empty()) ans+= p_arr.top();
    cout<< ans;
    
    
    
    return 0;
}