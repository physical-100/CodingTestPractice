#include <bits/stdc++.h>
using namespace std;

/*
산성은 10억 까지
알칼리는 -10억 
용액의 특성값의 합으로 정의 -> 같은 양의 두 용액을 혼합하여 특성값이 0에 가까운 용약 
어쨌든 두개를 더해서 0에 가장 가까우면 된다
정렬 필요 
*/
const int INF = 2*1e9+1;
vector<int> arr;
int n;
pair<int,int> ans;
int min_val = INF;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++){
        // 특성 값이 다 다르다. 
        //0은 존재 하지 않음.
        int n;
        cin>> n;
        arr.push_back(n);
    }
    sort(arr.begin(),arr.end());
    int r = n-1,l=0;
    while(1){
        int s = arr[r]+arr[l];
        if(abs(s)<= min_val) {
            min_val= abs(s);
            ans= {l,r};
        }
        if(s==0) 
            break;
        else if(s>0){
            r--;
        }
        else{
            l++;
        }
        if(l>=r){
            //cout<< l<<r<<'\n';
            break;  
        } 
    }
    //cout<< INF <<'\n';
    cout<<arr[ans.first]<<' '<<arr[ans.second];
    return 0;
}