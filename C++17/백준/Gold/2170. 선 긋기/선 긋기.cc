#include <bits/stdc++.h>
using namespace std;

#define X first
#define Y second

/*
그려진 선들의 총 길이를 구하는 프로그램 작성 
*/
int n;
pair<int,int> lines[1000001];
vector<pair<int,int>> ans; 
long long total;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>> lines[i].X>>lines[i].Y;
    }
    sort(lines,lines+n);
    int cur_x = lines[0].X;
    int cur_y = lines[0].Y;
    for(int i=1;i<n;i++){
        if(lines[i].X<=cur_y){ 
            // 이미 정렬을 했기 때문에 cur_X보다는 큰거나 같은 값이 들어옴 
            cur_y = max(cur_y, lines[i].Y);
        }
        else{
          //연결된 선이 아닌경우 
            total+= cur_y - cur_x;
            cur_x = lines[i].X;
            cur_y = lines[i].Y;
        }   
    }
    total+= cur_y - cur_x;
    cout<<total;
    return 0;
}