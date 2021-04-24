#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
#include<stdio.h>
using namespace std;

int N, X;
int arr[21][21];

int play() {
	int cnt = 0;

	// 상하 
	for (int x = 0; x < N; x++) {
		int k = 1;
		int cmp = arr[0][x];
		bool up = 0;

		int y = 1;
		while (y < N) {

			if (arr[y][x] == cmp) {
				k++;
				if (k == X) up = true;
			}
			else if (abs(arr[y][x] - cmp) > 1) break;
			else if (arr[y][x] - cmp == 1) { // 오르막길
				if (up == true) {
					k = 1;
					cmp = arr[y][x];
					up = 0;
				}
				else break;
			}
			else if (arr[y][x] - cmp == -1) { // 내려막길
				k = 1;
				cmp = arr[y][x];
				if (y + X - 1 < N) {
					for (int h = y + 1; h <= y + X - 1; h++) {
						if (arr[h][x] == cmp) k++;
					}
					if (k == X) {
						k = 0;
						up = 0;
						y = y + X - 1;
						if (y == N - 1) {
							cnt++;
							break;
						}
					}
					else break;
				}
				else break;
			}

			if (y == N - 1) {
				cnt++;
			}
			y++;
		}
	}

	// 좌 우
	for (int y = 0; y < N; y++) {
		int k = 1;
		int cmp = arr[y][0];
		bool up = 0;

		int x = 1;
		while (x < N) {

			if (arr[y][x] == cmp) {
				k++;
				if (k == X) up = true;
			}

			else if (abs(arr[y][x] - cmp) > 1) break;
			else if (arr[y][x] - cmp == 1) { // 오르막길
				if (up == true) {
					k = 1;
					up = 0;
					cmp = arr[y][x];
				}
				else break;
			}
			else if (arr[y][x] - cmp == -1) { // 내려 막길
				k = 1;
				cmp = arr[y][x];
				if (x + X - 1 < N) {
					for (int h = x + 1; h <= x + X - 1; h++) {
						if (arr[y][h] == cmp) k++;
					}
					if (k == X) {
						x = x + X - 1;
						k = 0;
						up = 0;
						if (x == N - 1) {
							cnt++;
							break;
						}
					}
					else break;
				}
				else break;
			}

			if (x == N - 1) {
				cnt++;
			}
			x++;
		}
	}

	return cnt;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;
	for (int p = 1; p <= T; p++) {
		
		cin >> N >> X;
		for (int y = 0; y < N; y++) {
			for (int x = 0; x < N; x++) {
				cin >> arr[y][x];
			}
		}
		cout << "#" << p << " " << play() << endl;
	}
}