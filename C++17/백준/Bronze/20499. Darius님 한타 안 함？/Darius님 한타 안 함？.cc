#include <bits/stdc++.h>
using namespace std;

int main() {
   int a, b, c;
    scanf("%d/%d/%d", &a, &b, &c); // 아예 입력받을 때 형식을 지정해버림
    
    if (a + c < b || b == 0) cout << "hasu";
    else cout << "gosu";
    return 0;
}