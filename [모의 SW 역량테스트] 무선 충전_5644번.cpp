#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
#include<cstring>
#include<stdio.h>
using namespace std;

int M, Q;
int arr[2][101];
int visited[11][11];
vector<pair<int,int>> map[11][11];

int dx[] = { 0,0,1,0,-1 }; 
int dy[] = { 0,-1,0,1,0 };

pair<int, int> A, B;

bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.second > b.second;
}

void bfs(int cy, int cx, int c, int po, int num) {
	memset(visited, false, sizeof(visited));
	queue<pair<int,pair<int, int>>> q;
	visited[cy][cx] = true; 
	q.push({ 0,{ cy,cx } });
	map[cy][cx].push_back({ num,po });
	
	while (!q.empty()) {

		int cnt = q.front().first;
		int y = q.front().second.first;
		int x = q.front().second.second;
		q.pop();
		
		for (int i = 1; i <= 4; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];
			if (1 <= ny && ny <= 10 && 1 <= nx && nx <= 10 && !visited[ny][nx]) {
				if (cnt < c) {
					q.push({ cnt + 1,{ny,nx } });
					visited[ny][nx] = true;
					map[ny][nx].push_back({ num,po });
				}
			}
		}
	}
}

int cmp_bp(int ay, int ax, int by, int bx) {

	if (map[ay][ax].size() == 0 && map[by][bx].size() == 0) return 0; 
	else if(map[ay][ax].size() ==0) return map[by][bx][0].second;
	else if (map[by][bx].size() == 0) return map[ay][ax][0].second;

	if (map[ay][ax].size() == 1 && map[by][bx].size() == 1) {
		if (map[ay][ax][0].first == map[by][bx][0].first) return map[ay][ax][0].second;
		else return map[ay][ax][0].second + map[by][bx][0].second;
	}
	else if (map[ay][ax].size() == 1) {
		if (map[ay][ax][0].first == map[by][bx][0].first) return map[ay][ax][0].second + map[by][bx][1].second;
		else return map[ay][ax][0].second + map[by][bx][0].second;
	}
	else if (map[by][bx].size() == 1) {
		if (map[ay][ax][0].first == map[by][bx][0].first) return map[ay][ax][1].second + map[by][bx][0].second;
		else return map[ay][ax][0].second + map[by][bx][0].second;
	}
	else if (map[by][bx].size() > 1 && map[ay][ax].size() > 1) {
		if (map[ay][ax][0].first == map[by][bx][0].first) return max(map[ay][ax][1].second + map[by][bx][0].second, map[ay][ax][0].second + map[by][bx][1].second);
		else return map[ay][ax][0].second + map[by][bx][0].second;
	}
}

int move() {

	int sum = 0;
	for (int h = 0; h <= M; h++) {
				
		int ay = A.first + dy[arr[0][h]];
		int ax = A.second + dx[arr[0][h]];

		int by = B.first + dy[arr[1][h]];
		int bx = B.second + dx[arr[1][h]];
		
		sum += cmp_bp(ay, ax, by, bx);

		A.first = ay; A.second = ax;
		B.first = by; B.second = bx;		
	}
	return sum;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	freopen("1.txt", "r", stdin); 
	int T;
	cin >> T;
	for (int p = 1; p <= T; p++) {

		for (int y = 1; y <= 10; y++) {
			for (int x = 1; x <= 10; x++) {
				map[y][x].clear();
			}
		}

		cin >> M >> Q;
		for (int g = 0; g <= 1; g++) {
			for (int h = 1; h <= M; h++) {
				cin >> arr[g][h];
			}
		}
		int y, x, c, po;
		for (int i = 0; i < Q; i++) {
			cin >> x >> y >> c >> po; 
			bfs(y, x, c, po, i + 1);
		}

		A = { 1,1 }; 
		B = { 10,10 };

		for (int y = 1; y <= 10; y++) {
			for (int x = 1; x <= 10; x++) {
				sort(map[y][x].begin(), map[y][x].end(), cmp);
			}
		}
		cout << "#" << p << " " << move() << endl;
	}
}