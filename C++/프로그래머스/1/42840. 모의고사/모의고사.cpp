#include<bits/stdc++.h>

using namespace std;
vector<vector<int>> person = {{1,2,3,4,5},{2,1,2,3,2,4,2,5},
        {3,3,1,1,2,2,4,4,5,5}};

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    vector<int> tmp; 
    for(auto c : person){
        int len = c.size(), cnt=0;
        //cout <<len<<'\n';
        for(int i=0;i<answers.size();i++){
            int idx = i%len;
            if(answers[i]==c[idx]) cnt++;
        }
        tmp.push_back(cnt);
    }
    int mx = *max_element(tmp.begin(),tmp.end());
    for(int i=0;i<3;i++)
        if(tmp[i]==mx) answer.push_back(i+1);
    return answer;
}