#include <iostream>
#include <vector>

using namespace std;

// 국가 정보를 담을 구조체
struct Country {
    int id;
    int gold;
    int silver;
    int bronze;
};

int main() {
    // 입출력 속도 향상 (선택 사항이지만 습관들이면 좋음)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    vector<Country> countries(N);
    
    // 우리가 등수를 알고 싶은 K 국가의 메달 정보를 저장할 변수
    int k_gold = 0, k_silver = 0, k_bronze = 0;

    // 1. 입력 받기
    for (int i = 0; i < N; i++) {
        cin >> countries[i].id >> countries[i].gold >> countries[i].silver >> countries[i].bronze;
        
        // 입력받는 국가가 K라면 따로 메달 정보 저장해두기
        if (countries[i].id == K) {
            k_gold = countries[i].gold;
            k_silver = countries[i].silver;
            k_bronze = countries[i].bronze;
        }
    }

    // 2. 나보다 더 잘한 나라 세기
    int rank = 1; // 기본 1등부터 시작

    for (int i = 0; i < N; i++) {
        // 자기 자신(K)과는 비교할 필요 없음 (같으면 무시됨)
        if (countries[i].id == K) continue;

        // 비교 로직: 금 -> 은 -> 동 순서
        if (countries[i].gold > k_gold) {
            rank++;
        } 
        else if (countries[i].gold == k_gold) {
            if (countries[i].silver > k_silver) {
                rank++;
            } 
            else if (countries[i].silver == k_silver) {
                if (countries[i].bronze > k_bronze) {
                    rank++;
                }
            }
        }
    }

    // 3. 결과 출력
    cout << rank << "\n";

    return 0;
}