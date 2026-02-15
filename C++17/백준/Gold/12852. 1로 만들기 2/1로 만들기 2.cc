#include<bits/stdc++.h>

using namespace std;

int dist[1000001];  // 최소 횟수 저장
int parent[1000001]; // 경로 추적용 (이전 숫자 저장)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    dist[1] = 0;
    for (int i = 2; i <= n; i++) {
        // 1. 기본적으로 1을 빼는 경우
        dist[i] = dist[i - 1] + 1;
        parent[i] = i - 1;

        // 2. 2로 나누어 떨어지고, 그게 더 빠를 때
        if (i % 2 == 0 && dist[i] > dist[i / 2] + 1) {
            dist[i] = dist[i / 2] + 1;
            parent[i] = i / 2;
        }

        // 3. 3으로 나누어 떨어지고, 그게 더 빠를 때
        if (i % 3 == 0 && dist[i] > dist[i / 3] + 1) {
            dist[i] = dist[i / 3] + 1;
            parent[i] = i / 3;
        }
    }

    // 최소 연산 횟수 출력
    cout << dist[n] << "\n";

    // 경로 추적 출력
    int current = n;
    while (true) {
        cout << current << " ";
        if (current == 1) break;
        current = parent[current];
    }

    return 0;
}