#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<cmath>
using namespace std;

int N,K;
char arr[28];
vector<int> v;

bool cmp(int a, int b) {
	return a > b;
}

void play() {

	int slade = N / 4;

	int idx = 0;
	for (int r = 0; r < slade; r++) {

		for (int i = idx + r; i < idx + r + N; i += slade) {
			int sum = 0;
			for (int j = 0; j < slade; j++) {
				char temp = arr[(i + j) % N];

				int num = 0;
				if ('0' <= temp && temp <= '9') {
					num = temp - '0';
				}
				else if ('A' <= temp && temp <= 'F') {
					num = temp - 'A' + 10;
				}
				sum += pow(16, slade - 1 - j) * num;
			}
			v.push_back(sum);
		}		
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int T; 
	cin >> T;
	for (int p = 1; p <= T; p++) {

		v.clear();

		string input;
		cin >> N >> K;
		cin >> input;
		for (int i = 0; i < N; i++) {
			arr[i] = input[i];
		}

		play();

		sort(v.begin(),v.end(),cmp);
		
		int idx = 1;
		int cnt = 1; 
		int cmp = v[0];

		while (true) {
			if (cnt == K) break;
			else if (idx < v.size() && cmp == v[idx]) idx++;
			else if (cmp != v[idx]){
				cmp = v[idx];
				cnt++;
				idx++;
			}
		}
		cout << "#" << p << " "<< cmp << endl;
	}
}