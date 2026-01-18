    #include <bits/stdc++.h>
using namespace std;
#define X first
#define Y second

/*격자의 각 칸에는 바구니가 있고 저장할 수 있는 물의 양 제한 x
1 <-> N 행과 열은 연결되어 있음 
비바라기를 시전하면 (N,1) , (N,2)(N-1,1)(N-1,2) 에 비구름이 생김 
구름에 이동을 M번 명령  
각 이동 명령은 방향과 거리로 이루어져있음 총 8개의 방향 
이동 과정
    1. 모든 구름이 d_i방향으로 s_i칸 이동 
    2. 각 구름에서 비가 내려 바구니에 저장된 물의 양 1증가 
    3. 구름이 모두 사라짐 
    4. 2에서 물이 증가한 칸에서 물복사 버그  
        -> 대각선 방향으로 거리가 1인 칸에 물이 있는 바구니 수만큼 r,c의 물의 양이 증가한다. 
        경계를 넘어가는 칸은 대각선 방향으로 거리가 1이 아님
    5. 바구니의 저장된 물의 양이 2이상인 모든 칸에서 구름 생성 + 물의 양이 2  줄어듦 . 
        -> 3에서 구름이 사라진 칸은 제외 
    M번의 이동이 끝난후 바구니에 들어 있는 물의 양의 합을 구하자 
*/
int N, M, ans;
int board[55][55];
bool is_prev_cloud[55][55]; // 사라진 구름 위치 표시용
vector<pair<int, int>> clouds;
// 1번(←)부터 시작하도록 dx, dy 인덱스 조정 (0번은 비워둠)
int dx[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dy[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) cin >> board[i][j];

    // 초기 구름 위치
    clouds.push_back({N - 1, 0}); clouds.push_back({N - 1, 1});
    clouds.push_back({N - 2, 0}); clouds.push_back({N - 2, 1});

    while (M--) {
        int d, s; cin >> d >> s;
        memset(is_prev_cloud, 0, sizeof(is_prev_cloud));
        vector<pair<int, int>> moved_clouds;

        // 1 & 2. 구름 이동 및 비 내리기
        for (auto cur : clouds) {
            int nr = (cur.X + dx[d] * (s % N) + N) % N;
            int nc = (cur.Y + dy[d] * (s % N) + N) % N;
            board[nr][nc]++;
            moved_clouds.push_back({nr, nc});
            is_prev_cloud[nr][nc] = true; // 3. 구름이 사라진 위치 기록
        }
        clouds.clear();

        // 4. 물복사 버그 (대각선: 2, 4, 6, 8 방향)
        for (auto cur : moved_clouds) {
            int cnt = 0;
            for (int i = 2; i <= 8; i += 2) {
                int nr = cur.X + dx[i];
                int nc = cur.Y + dy[i];
                if (nr < 0 || nc < 0 || nr >= N || nc >= N) continue;
                if (board[nr][nc] > 0) cnt++;
            }
            board[cur.X][cur.Y] += cnt;
        }

        // 5. 새로운 구름 생성
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] >= 2 && !is_prev_cloud[i][j]) {
                    board[i][j] -= 2;
                    clouds.push_back({i, j});
                }
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) ans += board[i][j];
    cout << ans;
}