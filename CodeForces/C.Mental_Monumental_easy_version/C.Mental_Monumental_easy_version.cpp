#include <bits/stdc++.h>
using namespace std;

/*
어떤 수 x로 y를 만들려면 x는 최소한 2y+1이거나, 아니면 원래부터 x=y여야 한다. 
1. 배열에 존재하는 숫자는 그대로 사용 
2. 쓰이지 않은 나머지 숫자를 available에 담는다 
3. 부족한 숫자 챙기기 -> 0~ m-1까지 중 배열에 없었던 숫자를 missing에 담는다. 
4. 역순 그리디 매칭 
이분탐색이 필요하다  왜냐하면 미래를 모름 -> 이분탐색으로 가능한지를 확인 
skip 말고 그냥 가능한지만 확인 

*/

// MEX m을 만들 수 있는지 확인하는 함수
bool check(int m, int n, const vector<int>& a) {
    if (m == 0) return true;

    vector<int> missing;
    vector<int> available;

    int ptr = 0;
    for (int v = 0; v < m; ++v) {
        // v로 쓸 수 없는 작은 숫자들은 여유분(available)으로 버림
        while (ptr < n && a[ptr] < v) {
            available.push_back(a[ptr++]);
        }
        // v가 배열에 있다면 하나는 '직접' 사용 (깎지 않고 보존!)
        if (ptr < n && a[ptr] == v) {
            ptr++;
            // 같은 숫자가 또 나오면 그건 중복이니까 여유분으로 넣음
            while (ptr < n && a[ptr] == v) {
                available.push_back(a[ptr++]);
            }
        } else {
            // 배열에 없는 숫자는 나중에 깎아서 만들어야 하니 missing에 기록
            missing.push_back(v);
        }
    }
    
    // 타겟 M 이상인 아주 큰 숫자들은 모두 깎아 쓸 수 있는 든든한 여유분
    while (ptr < n) {
        available.push_back(a[ptr++]);
    }

    if (missing.size() > available.size()) return false;

    // 큰 부족함(missing)부터 큰 여유분(available)으로 채워나감
    int m_idx = missing.size() - 1;
    int a_idx = available.size() - 1;
    while (m_idx >= 0) {
        // 깎아서 만들 수 있는 조건 확인
        if (available[a_idx] < 2 * missing[m_idx] + 1) return false;
        m_idx--;
        a_idx--;
    }

    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    sort(a.begin(), a.end());

    // 이분 탐색으로 안전하고 확실하게 최대 MEX 찾기
    int low = 0, high = n + 1, ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid, n, a)) {
            ans = mid;
            low = mid + 1; // 더 큰 MEX도 가능한지 탐색
        } else {
            high = mid - 1; // 불가능하면 범위를 낮춤
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
