#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;  // 예: "FFFFFF" 또는 "1a2b3c"

    long long ans = 0;
    
    // 문자열을 16진수로 해석해서 10진수로 변환
    ans = stoll(s, nullptr, 16);
    
    cout << ans << endl;
    
    return 0;
}