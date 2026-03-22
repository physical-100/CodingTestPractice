#include <bits/stdc++.h>
using namespace std;

int n;
/*
두 수는 달라야하ㅏ며 첫번째 수가 두번째 수보다 작아야한다 
*/

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int T;
    cin>> T;
    while(T--){
        cin >> n;
        cout<<"Pairs for "<<n<<":";
        for(int i=1;i<((n+1)/2);i++){
            if(i>1) cout<<',';
            cout <<' '<<i<<' '<<n-i;
        }
        cout<<'\n';
    }
    return 0;
}