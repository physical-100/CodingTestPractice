#include <bits/stdc++.h>
using namespace std;

/*
A,B는 모두 자연수  두 분수의 합 또한 분수로 표현 가능 
기약 분수의 형태로 구하는 프로그램 작성 
기약 분수란? 더 이상 약분 되지 않는 분수
수학 정수론 
유클리드 호제법
두 수 a,b, (단, a>b)에 대해:
    a mod b(나머지)를 구하고,
        a를 b로, b를 나머지로 바꿔 반복.
        나머지가 0이 되면, 그때의 b가 최대공약수.
*/

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    int num = 0,den = 0;
    int max_divide = 0;
    
    den = b*d;
    num = a*d+b*c;
    

    while(den % num != 0){
        int tmep = den % num;
        den = num;
        num = tmep;
    }
    max_divide = num;
    
    cout << (a*d+b*c)/max_divide <<' '<< b*d/max_divide ;
    return 0;
}