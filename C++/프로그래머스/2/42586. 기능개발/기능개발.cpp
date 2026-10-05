#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    vector<int> remains;
    int max_t=0;
    int r;
    for(int i=0;i<speeds.size();i++){
        r =  (99-progresses[i])/speeds[i]+1;
        if(answer.empty()||max_t<r) answer.push_back(1);
        else ++answer.back();
        if(max_t<r) max_t =r;
        
        }

    return answer;
}