#include<bits/stdc++.h>
using namespace std;
//값을 증가
bool isPrime(int n){
    if(n<2)return 0;
    for(int i=2;i*i<=n;i++){
        if(n%i==0) {
            return 0;
        }
    }
    return 1;
}
int solution(string numbers) {
    int answer = 0;
    set<int> possible; //중복 제거 및 순차 
    sort(numbers.begin(),numbers.end()); //숫자 크기순으로 정렬 
    int n= numbers.length();
    for(int r=1;r<=n;r++){
        vector<int> idx (n,0);
        for(int i=0;i<r;i++) idx[n-i-1] = 1; //뒤에서부터 채움 
        
        do{
            string s ="";
            for(int i=0;i<n;i++){
                if(idx[i]) s+=numbers[i];
            }
            string sec = s;
            do{
                int val = stoi(sec);
                possible.insert(val);
            }while(next_permutation(sec.begin(),sec.end()));
            
        }while(next_permutation(idx.begin(),idx.end()));
    }
    for(int tmp : possible){
        if(isPrime(tmp)){
            answer++;
        }
    }
    
    return answer;
}