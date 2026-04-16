#include <bits/stdc++.h>
using namespace std;
/*
최대 1000,000이라서 NlogN인 이분탐색을 활용해야한다 

lower_bound를 쓰면 아주 간단해짐 
사용법:  lower_bound(lists.begin(),lists,end(), arr[i]);
*/
vector<long long> lists;
int n;
long long arr[1000001];
int pos[1000001];
//arr의 값이 lists의 몇번째 인덱스로 들어갔는지 찾는 배열 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> n;
    for(int i=0;i<n;i++)cin>>arr[i];
    lists.push_back(arr[0]);
    pos[0]= 0;
    for(int i=1;i<n;i++){
        if(arr[i]>lists.back()) {
            lists.push_back(arr[i]);
            //새로 추가하게 되면 마지막 인덱스를 넣음 
            pos[i]= lists.size()-1;
        }
        else{
            auto it = lower_bound(lists.begin(),lists.end(),arr[i]);
            //it는 위치를 가리키는 반복자(포인터) 
            pos[i] = it-lists.begin();
            *it = arr[i];
        }
    }
    int s= lists.size();
    stack<long long> st;
    int target = s-1;
    for (int i = n - 1; i >= 0; i--) {
        if (pos[i] == target) {
            st.push(arr[i]);
            target--; // 다음으로 찾을 인덱스는 하나 작은 값
        }
        if (target < 0) break; // 다 찾았으면 종료
    }
    cout<< s<<'\n';
    while(!st.empty()){
        cout<<st.top()<<' ';
        st.pop();
    }
    return 0;
}