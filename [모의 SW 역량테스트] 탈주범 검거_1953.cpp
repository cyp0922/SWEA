#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;

int N, M, L;
int arr[51][51];
bool visited[51][51];
int ans = 0;

struct is {
	int y;
	int x;
	int cnt;
	int shape;
};

int dx[] = { -1,0,1,0 }; // ¼­ ºÏ µ¿ ³²
int dy[] = { 0,-1,0,1 };

void print() {

	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			cout << visited[y][x];
		}
		cout << endl;
	}
	cout << endl;

}

void bfs(int cy, int cx) {
	queue <is> q;
	visited[cy][cx] = true;
	q.push({ cy,cx,0,arr[cy][cx] });
	int sum = 1;

	while (!q.empty()) {

		int y = q.front().y;
		int x = q.front().x;
		int cnt = q.front().cnt;
		int shape = q.front().shape;
		q.pop();

		ans = max(ans, sum);

		int a=0, b=0, c=0;
		// ¼­ ºÏ µ¿ ³² 0 1 2 3
		if (shape == 1) {
			a = 0;
			b = 3;
			c = 1;
		}
		else if (shape == 2) {
			a = 1;
			b = 3;
			c = 2;
		}
		else if (shape == 3) {
			a = 0;
			b = 2;
			c = 2;
		}
		else if (shape == 4) {
			a = 1;
			b = 2;
			c = 1;
		}
		else if (shape == 5) {
			a = 2;
			b = 3;
			c = 1;
		}
		else if (shape == 6) {
			a = 0;
			b = 3;
			c = 3;
		}
		else if (shape == 7) {
			a = 0;
			b = 1;
			c = 1;
		}

		for (int i = a; i <= b; i += c) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (0 <= ny && ny < N && 0 <= nx && nx < M) {
				if (!visited[ny][nx] && cnt + 1 < L) {
					if (i == 0) { // ¼­
						if (arr[ny][nx] == 1 || arr[ny][nx] == 3 || arr[ny][nx] == 4 || arr[ny][nx] == 5) {
							visited[ny][nx] = true;
							sum++;
							q.push({ ny,nx,cnt + 1,arr[ny][nx] });
						}
					}
					else if (i == 1) { // ºÏ
						if (arr[ny][nx] == 1 || arr[ny][nx] == 2 || arr[ny][nx] == 5 || arr[ny][nx] == 6) {
							visited[ny][nx] = true;
							sum++;
							q.push({ ny,nx,cnt + 1,arr[ny][nx] });
						}
					}
					else if (i == 2) { // µ¿
						if (arr[ny][nx] == 1 || arr[ny][nx] == 3 || arr[ny][nx] == 6 || arr[ny][nx] == 7) {
							visited[ny][nx] = true;
							sum++;
							q.push({ ny,nx,cnt + 1,arr[ny][nx] });
						}
					}
					else if (i == 3) { // ³²
						if (arr[ny][nx] == 1 || arr[ny][nx] == 2 || arr[ny][nx] == 4 || arr[ny][nx] == 7) {
							visited[ny][nx] = true;
							sum++;
							q.push({ ny,nx,cnt + 1,arr[ny][nx] });
						}
					}
				}
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;
	for (int p = 1; p <= T; p++) {

		int sy, sx;
		ans = 0;
		cin >> N >> M;
		cin >> sy >> sx >> L;

		memset(visited, false, sizeof(visited));

		for (int y = 0; y < N; y++) {
			for (int x = 0; x < M; x++) {
				cin >> arr[y][x];
			}
		}
		bfs(sy, sx);
		cout << "#" << p << " " << ans << endl;
	}
	return 0;
}