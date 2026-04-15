#include <bits/stdc++.h>
using  namespace std;
const int INF = 1e9;
/*

 자신이 사용하고 있는 전기 용품의 사용 순서를 파악하여 플러그를 뺴는 횟수를 최소화 하는 방안 마련 
 n : 멀티탭의 개수 
 k : 사용 순서 
 각각의 멀티탭이 꽂힐 때 다음에 언제 등장하는지를 확인한다. 
*/

int n,k;
int arr[101];
bool used[101]; //현재 멀티탭에 꽂혀있는지를 확인
int ans;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>k;
    vector<int> tabs; //<순서, 다음에 등장 번호> 
    for(int i=0;i<k;i++){
        cin>> arr[i];
    }
    for(int i=0;i<k;i++){
        //이미 꽂힌 기기는 Pass
        if(used[arr[i]]) continue;
        
        //멀티탭이 비어 있을때 그냥 넣음 
        if(tabs.size()<n){
            tabs.push_back(arr[i]);
            used[arr[i]]=1;
        }
        else{
             //넘칠 때는 전수 조사
            int target_idx = -1;
            int last_pos = -1;
            
            for(int j=0;j<n;j++){
                int tmp_next = INF;
                for(int g=i+1;g<k;g++){
                    //다음에 등장하는거랑 동일한지 확인 
                    if(tabs[j]==arr[g]){
                        tmp_next=g;
                        break;
                    }
                }
                if(tmp_next>last_pos){
                    last_pos = tmp_next;
                    target_idx = j;
                }   
            }
            used[tabs[target_idx]] = 0;
            ans++;
            tabs[target_idx] = arr[i];
            used[arr[i]] = 1;
        }      
    }
    cout<<ans;
    
    return 0;
}