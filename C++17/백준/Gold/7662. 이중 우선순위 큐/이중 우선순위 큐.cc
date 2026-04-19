#include <bits/stdc++.h>
using namespace std;

int t;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>t;
    while(t--){
        int n;
        cin >>n;
        multiset<int> ms;
        //최솟값 ms.begin()  , 최대값 ms.rbegin() or --ms.end()
        //erase 안에는 반복자를 넣으면 1개만 삭제 
        //erase 안에 값을 찾으면 찾아서 지우느라 더 오래 걸림 
        while(n--){
            char c ; int val;
            cin>> c>>val;
            if(c=='I')ms.insert(val);
            else if(c=='D'){
                if(ms.empty()) continue;
                if(val ==-1){
                    //최솟값 삭제
                    ms.erase(ms.begin());
                }
                else{
                    ms.erase(--ms.end()); 
                }//최댓값 삭제
            }
        }
        if(ms.empty()) cout<< "EMPTY\n";
        else cout<< *(--ms.end()) <<' '<< *ms.begin()<<'\n';
    }
    return 0;
}