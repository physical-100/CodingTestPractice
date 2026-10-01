#include<bits/stdc++.h>

using namespace std;

vector<int> solution(vector<int> arr) 
{
    vector<int> answer;
    stack<int> s1;
    for(int i=arr.size()-1;i>=0;i--){
        if(s1.empty()) s1.push(arr[i]);
        if(s1.top()!= arr[i]) s1.push(arr[i]);
    }
    
    while(!s1.empty()){
        answer.push_back(s1.top()); 
        s1.pop();
    }    

    return answer;
}