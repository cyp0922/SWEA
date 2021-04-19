#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#include<vector>
#include<stdio.h>
using namespace std;

int N, M;
int arr[21][21];
bool visited[21][21];

struct is {
    int y;
    int x;
    int k;
};

int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
int MAX = 0;

void bfs(int cy, int cx) {

    memset(visited, false, sizeof(visited));
    queue<is> q;
    int home = 0;
    visited[cy][cx] = true;
    if (arr[cy][cx]) home++;
    q.push({ cy,cx,1});
    int Be = 0;

    if ( M * home - 1 >= 0) MAX = max(MAX, home);

    while (!q.empty()) {

        int y = q.front().y;
        int x = q.front().x;
        int k = q.front().k;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (0 <= ny && ny < N && 0 <= nx && nx < N) {
                if (!visited[ny][nx]) {
                    if (arr[ny][nx] == 0) {
                        q.push({ ny,nx,k + 1 });
                        visited[ny][nx] = true;
                    }
                    else if (arr[ny][nx] == 1) {
                        q.push({ ny,nx,k + 1 });
                        home++;
                        visited[ny][nx] = true;
                    }
                }
            }
        }

        if (!q.empty() && Be != q.front().k) {
            int temp = q.front().k;
            int num = M * home - (temp * temp + (temp - 1) * (temp - 1));
            if (num >= 0) MAX = max(MAX, home);
            Be = q.front().k;
        }
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen("2.txt", "r", stdin);

    int T;
    cin >> T;
    for (int p = 1; p <= T; p++) {

        MAX = 0;
        cin >> N >> M;

        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                cin >> arr[y][x];
            }
        }

        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++) {
                bfs(y, x);
            }
        }

        cout << "#" << p << " " << MAX << endl;
    }
}