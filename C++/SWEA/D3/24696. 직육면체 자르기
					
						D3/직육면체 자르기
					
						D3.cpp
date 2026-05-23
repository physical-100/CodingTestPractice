#include<bits/stdc++.h>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
		long long  A, B,C ;
        cin >> A>>B>>C ; 
        long long node = A*B*C -1 ;
        if(node%2 ==0 ) cout<<2 <<'\n';
        else cout <<1<<'\n' ;


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}