#include<bits/stdc++.h>

using namespace std;

// 학생 정보를 담을 구조체
struct Student {
    string name;
    int kor, eng, math;
};

// 정렬 기준을 정의하는 비교 함수
bool compare(const Student& a, const Student& b) {
    if (a.kor != b.kor) {
        return a.kor > b.kor; // 1. 국어 내림차순
    }
    if (a.eng != b.eng) {
        return a.eng < b.eng; // 2. 영어 오름차순
    }
    if (a.math != b.math) {
        return a.math > b.math; // 3. 수학 내림차순
    }
    return a.name < b.name;     // 4. 이름 사전순 오름차순
}

int main() {
    // 입출력 최적화
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<Student> v(N);
    for (int i = 0; i < N; i++) {
        cin >> v[i].name >> v[i].kor >> v[i].eng >> v[i].math;
    }

    // 정의한 compare 함수를 기준으로 정렬
    sort(v.begin(), v.end(), compare);

    // 결과 출력
    for (int i = 0; i < N; i++) {
        cout << v[i].name << "\n";
    }

    return 0;
}