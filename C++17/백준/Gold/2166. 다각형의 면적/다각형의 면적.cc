#include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second

int N; 

vector<pair<long long ,long long>> edges; 

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>> N;
    for(int i=0;i<N;i++){
        long long a,b;
        cin>> a>>b;
        edges.push_back({a,b});// 순서대로 주어짐 
    }
    double area = 0;
    //신발끈 공식 적용 
    for(int i=0;i<N;i++){
        int j = (i+1)%N;
        area+= edges[i].X*edges[j].Y;
        area-= edges[i].Y*edges[j].X;
    }
    printf("%.1lf",(abs(area)/2.0));
    return 0;
}