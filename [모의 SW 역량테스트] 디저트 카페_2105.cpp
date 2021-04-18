#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;

int N;
int arr[21][21];
bool visited[21][21];
bool dessert[101];
int dy[] = { 1,1,-1, -1 }; //¿ìÇÏ ÁÂÇÏ ÁÂ»ó ¿ì»ó
int dx[] = { 1,-1,-1, 1 };

int MAX = 0;
int ky = 0; 
int kx = 0;

void print() {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			cout << visited[y][x];
		}
		cout << endl;
	}
	cout << endl;
}

void dfs(int y, int x, int dir, int cnt) {

	if (dessert[arr[y][x]]) return;
	

	dessert[arr[y][x]] = true;

	int ny; int nx; 
	ny = y + dy[dir];
	nx = x + dx[dir];
	if (0 <= ny && ny < N && 0 <= nx && nx < N) {
		if (dir == 3) {
			if (ny == ky && nx == kx) MAX = max(MAX, cnt);
		}
		if (!visited[ny][nx]) {
			visited[ny][nx] = true;
			dfs(ny, nx, dir, cnt +1);
			visited[ny][nx] = false;
		}
	}
	if (cnt != 1) {
		ny = y + dy[(dir + 1) % 4];
		nx = x + dx[(dir + 1) % 4];
		if (0 <= ny && ny < N && 0 <= nx && nx < N) {
			if (dir == 2) {
				if (ny == ky && nx == kx) MAX = max(MAX, cnt);
			}
			if (!visited[ny][nx]) {
				visited[ny][nx] = true;
				dfs(ny, nx, dir + 1, cnt + 1);
				visited[ny][nx] = false;
			}
		}
	}
	dessert[arr[y][x]] = false;
}


int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	freopen("2.txt", "r", stdin);

	int T;
	cin >> T;
	for (int p = 1; p <= T; p++) {

		memset(dessert, false, sizeof(dessert)); 
		memset(visited, false, sizeof(visited));
		MAX = 0;

		cin >> N;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> arr[y][x];
			}
		}

		for (int y = 0; y < N-2; y++) {
			for (int x = 1; x < N-1; x++) {
				visited[y][x] = true;
				ky = y;
				kx = x;
				dfs(y, x, 0, 1);
				visited[y][x] = false;	
			}
		}
		cout << "#" << p << " " << (MAX == 0 ? -1 : MAX) << "\n";
	}
}