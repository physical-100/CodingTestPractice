#include <bits/stdc++.h>
using namespace std;
/*
길이가 n이 수식 -> 정수와 연산자로 이뤄짐 
연산자의 우선 순위는 모두 동일 
왼쪽 부터 수식 계산  => 괄호를 추가하면  괄호의 값 부터 계산을 한다.
 -> 괄호 안에는 연산자가 하나만 들어있어야함  -> 중첩 괄호는 사용할 수 없다 

왼쪽에서부터 계산  
*/
int n ; 
char c[19];
int mx = INT_MIN;
int cal (int cur , char op , int num){
    switch (op) {
        case '+':
            cur += num;
            break;
        case '-':
            cur -= num;
            break;
        default:
            cur *= num;
    }
    return cur;
}
void func (int k,int cur_val){
    if(k>=n-1){
        mx = max(mx,cur_val);
        return ; 
    }
    int nxt_val = cal(cur_val ,c[k+1],c[k+2]-'0');
    func(k+2,nxt_val);
    if(k+4 <n){
        int back_val = cal(c[k+2]-'0',c[k+3],c[k+4]-'0');
        int get_val =  cal(cur_val ,c[k+1],back_val);
        func(k+4 , get_val);
    }
    
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> n;
    for(int i=0;i<n;i++)cin >> c[i];
    func(0,c[0]-'0');
    cout << mx;
    return 0;
}