#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<stdio.h>
#include<algorithm>
using namespace std;

int N, W, H;
int arr[16][13];
int cmp[16][13];
bool visited[16][13];
vector<int> order;
int MIN = 1e9;

int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

void down() {
	for (int x = 0; x < W; x++) {
		int idx = H - 1;
		for (int y = H - 1; y >= 0; y--) {
			if (cmp[y][x] && idx >= 1) {
				if (idx == y) idx--;
				else {
					cmp[idx][x] = cmp[y][x];
					cmp[y][x] = 0;
					idx--;
				}
			}
		}
	}
}

void POP(int y,int x) {

	visited[y][x] = true;
	int temp = cmp[y][x];
	cmp[y][x] = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < temp; j++) {
			int ny = y + j * dy[i];
			int nx = x + j * dx[i];
			if (0 <= ny && ny < H && 0 <= nx && nx < W && !visited[ny][nx]) {
				visited[ny][nx] = true;
				POP(ny, nx);
			}
		}
	}
}

void play(int x) {
	for (int y = 0; y < H; y++) {
		if (cmp[y][x]) {
			POP(y, x);
			break;
		}
	}
}

void func(int cx, int cnt) {

	if (cnt == N) {
		memcpy(cmp, arr, sizeof(cmp)); 

		for (int i = 0; i < order.size(); i++) {
			memset(visited, false, sizeof(visited));
			play(order[i]);
			down();
		}

		int num = 0;
		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				if (cmp[y][x]) num++;
			}
		}
		MIN = min(MIN, num);
		return;
	}

	for (int i = 0; i < W; i++) {
		order.push_back(i);
		func(i, cnt + 1);
		order.pop_back();
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T; 
	cin >> T;
	for (int p = 1; p <= T; p++) {

		memset(arr, false, sizeof(arr));
		cin >> N >> W >> H;
		MIN = 1e9;

		for (int y = 0; y < H; y++) {
			for (int x = 0; x < W; x++) {
				cin >> arr[y][x];
			}
		}

		func(0,0);
		cout << "#" << p << " " << MIN << endl;
	}
}