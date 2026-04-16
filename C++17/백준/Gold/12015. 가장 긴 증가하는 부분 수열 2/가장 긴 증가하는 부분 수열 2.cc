#include <bits/stdc++.h>
using namespace std;
/*
최대 1000,000이라서 NlogN인 이분탐색을 활용해야한다 
DP는 O(N^2)
이분 탐색을 사용하는 방법 
같은 위치일때 같은 길이라면 끝값이 작을 수록 미래에 더 유리하다. 
덮어쓸 때 길이 자체는 정답으로 유지 하지만 이때 lists가 정답은 아니다. 

lower_bound를 쓰면 아주 간단해짐 
사용법:  lower_bound(lists.begin(),lists,end(), arr[i]);
*/
vector<int> lists;
int n;
int arr[1000001];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> n;
    for(int i=0;i<n;i++)cin>>arr[i];
    lists.push_back(arr[0]);
    for(int i=1;i<n;i++){
        if(arr[i]>lists.back()) lists.push_back(arr[i]);
        else{
            auto it = lower_bound(lists.begin(),lists.end(),arr[i]);
            *it = arr[i];
        }
    }
    cout<< lists.size();
    return 0;
}