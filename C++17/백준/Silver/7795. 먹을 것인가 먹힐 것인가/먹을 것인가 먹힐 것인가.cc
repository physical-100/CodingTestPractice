#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int N, M;
    cin >> N >> M;

    vector<int> A(N), B(M);
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < M; i++) cin >> B[i];

    // B 그룹만 정렬 (이분 탐색을 위함)
    sort(B.begin(), B.end());

    int count = 0;
    for (int i = 0; i < N; i++) {
        // A[i]보다 작은 숫자가 B에 몇 개 있는지 이분 탐색
        // lower_bound는 A[i]와 같거나 큰 숫자가 처음 나오는 위치를 반환
        count += lower_bound(B.begin(), B.end(), A[i]) - B.begin();
    }

    cout << count << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}