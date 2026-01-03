
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll x1, y1, r1;
    ll x2, y2, r2;
    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;

    ll dx = x1 - x2;
    ll dy = y1 - y2;
    __int128 distSq = (__int128)dx * dx + (__int128)dy * dy; // 안전하게 128비트 사용
    __int128 sum = (ll)r1 + (ll)r2;
    __int128 diff = llabs(r1 - r2);
    __int128 sumSq = sum * sum;
    __int128 diffSq = diff * diff;

    // 완전히 같은 원(중심 같고 반지름 같음) → 면적 겹침 YES
    if (dx == 0 && dy == 0 && r1 == r2) {
        cout << "YES\n";
        return 0;
    }

    // 면적 겹침의 판정:
    // 1) 중심거리^2 < (r1 + r2)^2  → 외접보다 가까워야 함
    // 2) 중심거리^2 != (|r1 - r2|)^2 → 내접이 아니어야 함
    // (완전포함: d^2 < diff^2 도 자동으로 1),2) 만족)
    bool overlap = (distSq < sumSq) && (distSq != diffSq);

    cout << (overlap ? "YES" : "NO") << '\n';
    return 0;
}
