#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> v;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N;
    int n;
    for(int i=0;i<N;i++){
        cin>>n;
        v.push_back(n);
    }
    sort(v.begin(),v.end());
    for(auto c:v)
        cout<< c<<'\n';
    return 0;
        
    
}