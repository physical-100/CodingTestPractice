#include <bits/stdc++.h>
using namespace std;
/*
새로운 빌딩이 들어올 때마다 
해당 빌딩을 볼 수 있는 이전 빌딩의 수를 더한다 

*/
stack<int> s; 
int N;

vector<int> heights;
long long ans ; 

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N ; 
    int h ; 
    for(int i =0; i< N; i++) { 
        cin >> h;
        heights.push_back(h);
    }
    for( int height: heights) {
        
        while(!s.empty() && s.top()<=height  )
                s.pop();
        
        ans +=  s.size();
        s.push(height);
    }
    cout << ans ; 
    return 0;
}