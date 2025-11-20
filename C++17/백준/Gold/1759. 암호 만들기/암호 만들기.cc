#include <bits/stdc++.h>
using namespace std;
/*
서로 다른 L개의 알파벳 소문자 
최소한 한개의 모음과 최소 두개의 자음으로 구성 
순서대로 정렬되었을것
암호로 사용했을 법할 문자의 종류 C가지
C개의 문자가 주어졌을 때 가능성 있는 암호를 추측
모음 : a,e,i,o,u 
자음 : 그 외
*/
int L,C;
char arr[17],password[17];
bool isused[17];

bool m(char a){
    return (a=='a'||a=='e'||a=='i'||a=='o'||a=='u');
}

void func(int k,int st){
    if(k==L){
        int m_num=0,j_num=0;
        for(int i=0;i<L;i++){
            //모음이면 숫자 증가
            if(m(arr[i])) m_num++;
            else j_num++;
        }
        if(m_num>=1&&j_num>=2){
            for(int i=0;i<L;i++)cout<<arr[i];
            cout <<'\n';
        }
    }
    for(int i=st;i<C;i++){
        arr[k] = password[i];
        func(k+1,i+1);
    }
    
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> L>> C;
    for(int i=0;i<C;i++) cin>>password[i];
    sort(password,password+C);
    
    func(0,0);
    return 0;
}