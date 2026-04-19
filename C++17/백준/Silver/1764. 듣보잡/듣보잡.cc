#include <bits/stdc++.h>
using namespace std;

int N , M;
map<string,int> names;
vector<string> common;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> N>>M;
    int total = N+M;
    int cnt = 0;
    while(total--) {
        string s;
        cin>>s;
        names[s]++;
        if(names[s]>1) {
            cnt ++;
            common.push_back(s);
        }
    }
    cout << cnt <<'\n';
    sort(common.begin(),common.end());
    for(auto c:common)cout << c <<'\n';
    
    
    
    return 0;
}