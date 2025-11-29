#include <bits/stdc++.h>
using namespace std;

/*
설정할 수 있는 높이의 최댓값을 출력

*/
long long N,M;
vector<long long> trees;
long long  answer;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M ;
    while(N--){
        long long temp;
        cin >> temp;
        trees.push_back(temp);
    }
    long long low =0;
    long long high =1000000000;
    while(low <= high){
        long long sum = 0;
        long long mid = (low+high)/2;
        for(auto c:trees){
            sum+= ((c-mid)>=0)? c-mid: 0;
        } 
        
        if (sum >= M) {
            answer = mid;      // 조건 만족 → 높이를 더 올려도 됨
            low = mid + 1;
        } else {
            high = mid - 1;    // 조건 불만족 → 높이를 낮춰야 함
        }

        
    }
    cout << answer;
    
}