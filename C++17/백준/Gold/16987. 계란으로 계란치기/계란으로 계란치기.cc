#include <bits/stdc++.h>
using namespace std;
/*
브루트포스 알고리즘이란? 가능한 모든 경우의 수를 계산하는 것
내구도 1~300 . 무게 1~300
가장 왼쪽의 계란을 들어서 하나를 치고 깨졌으면 넘어감.
처음부터 왼 ->-> 마지막 순으로 계란을 깸.
*/
int n ,ans;
int weights[8];
int dandan[8];
bool isbroken[8];

void func(int k){
    if(k==n){
        int broken_eggs = 0;
        for(int i=0;i<n;i++) if(isbroken[i])broken_eggs++;
        ans = max(ans,broken_eggs);
        //cout <<ans<<'\n';
        return;
    }
    //현재 계란이 깨져있을 때
    if(isbroken[k])func(k+1);
    else{
        bool can_hit = false;
         for(int i=0;i<n;i++){
            if(!isbroken[i]&&i!=k){
                //계란의 내구도 싸움
                can_hit=true;
                dandan[k] -= weights[i];
                dandan[i] -= weights[k];
                isbroken[k] = (dandan[k]>0)?0:1;
                isbroken[i] = (dandan[i]>0)?0:1;
                func(k+1);
                //다시 초기화
                dandan[k] += weights[i];
                dandan[i] += weights[k];
                isbroken[k] = 0;
                isbroken[i] = 0;
            } 
        } 
        if(!can_hit)func(k+1);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    //계란 초기화
    for(int i=0;i<n;i++) cin >>dandan[i] >>weights[i];
    func(0);
    cout<< ans;
    return 0;
}