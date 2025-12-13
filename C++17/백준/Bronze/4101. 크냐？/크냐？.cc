#include<iostream>
using namespace std;

int main(void){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(true){
        int n,m;
        cin >>n>>m;
        if(n==0&& m==0) break;
        if(n>m) cout << "Yes"<<'\n';
        else cout << "No"<<'\n';
    }
    return 0;
}