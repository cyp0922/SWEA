#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
#include<cstring>
#include<stdio.h>
using namespace std;

int N;
int arr[102][102];
int MAX = 0;

struct is {
	int y;
	int x;
};
is worm[2][5];

int dx[] = { -1, 0, 1, 0 }; // ¼­ ºÏ µ¿ ³²
int dy[] = { 0,-1,0,1 };

void func(int cy, int cx, int dir, int cnt) {

	int y = cy;
	int x = cx;
	int gap = 1;
	while (true) {	
		int ny = y + gap * dy[dir];
		int nx = x + gap * dx[dir];
		if (1 <= ny && ny <= N && 1 <= nx && nx <= N) {

			if (cy == ny && cx == nx) {
				MAX = max(MAX, cnt);
				return;
			}
			else if (arr[ny][nx] == -1) {
				MAX = max(MAX, cnt);
				return;
			}

			if (arr[ny][nx] > 5) {
				int temp = arr[ny][nx] - 5;
				gap = 0;
				if (worm[0][temp].y == ny && worm[0][temp].x == nx) {
					y = worm[1][temp].y; 
					x = worm[1][temp].x;
				}
				else {
					y = worm[0][temp].y;
					x = worm[0][temp].x;
				}
			}

			else if (1 <= arr[ny][nx] && arr[ny][nx] <= 5) {
				if (arr[ny][nx] == 1) {
					if (dir == 0) dir = 1;
					else if (dir == 3) dir = 2;
					else dir = (dir + 2) % 4;
				}
				else if (arr[ny][nx] == 2) {
					if (dir == 0) dir = 3;
					else if (dir == 1) dir = 2;
					else dir = (dir + 2) % 4;
				}
				else if (arr[ny][nx] == 3) {
					if (dir == 2) dir = 3;
					else if (dir == 1) dir = 0;
					else dir = (dir + 2) % 4;
				}
				else if (arr[ny][nx] == 4) {
					if (dir == 2) dir = 1;
					else if (dir == 3) dir = 0;
					else dir = (dir + 2) % 4;
				}
				else if (arr[ny][nx] == 5) dir = (dir + 2) % 4;
				
				cnt++;
				gap = 0;
				y = ny;
				x = nx;
			}
		}
		else {
			dir = (dir + 2) % 4;
			gap = 0;		
			y = ny;
			x = nx;
			cnt++;
		}	
		gap++;
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;

	for (int p = 1; p <= T; p++) {
		MAX = 0;

		memset(worm, false, sizeof(worm));

		cin >> N;
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				cin >> arr[y][x];
				if (arr[y][x] > 5) {
					if (worm[0][arr[y][x] - 5].y == 0 && worm[0][arr[y][x] - 5].x == 0) {
						worm[0][arr[y][x] - 5] = { y,x };
					}
					else worm[1][arr[y][x] - 5] = { y,x };					
				}
			}
		}

		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= N; x++) {
				if (arr[y][x] == 0) {
					for (int i = 0; i < 4; i++) {
						func(y, x, i, 0);
					}
				}
			}
		}
		cout << "#" << p << " " << MAX << endl;
	}
}