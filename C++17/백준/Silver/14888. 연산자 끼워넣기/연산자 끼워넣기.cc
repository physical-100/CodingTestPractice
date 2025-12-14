#include<bits/stdc++.h>
using namespace std;
/*
범위는 +- 10억 => int의 범위에 해당한다.
*/
int Mx_val = -10e8-1;
int Min_val = 10e8+1;
int numbers[100];
vector<int> possible;
int N;
int oper[4]; // +,-,x,% 

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    int k ;
    for(int i=0;i<N;i++) cin >> numbers[i];
    for(int i=0;i<4;i++) {
        cin >> oper[i];
        for(int j=0;j<oper[i];j++) possible.push_back(i);
    }
    do{
        int tmp = numbers[0];
        for(int i=1;i<N;i++){
            switch (possible[i-1]) {
                case 0:
                    tmp += numbers[i];
                    break;
                case 1:
                    tmp -= numbers[i];
                    break;
                case 2:
                    tmp *= numbers[i];
                    break;
                default :
                    tmp /= numbers[i];
                    
            }
        }
        Mx_val = max(Mx_val,tmp);
        Min_val = min(Min_val,tmp);
    }while(next_permutation(possible.begin(),possible.end()));
    cout <<Mx_val<<'\n'<< Min_val;
}