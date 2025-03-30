#include <iostream>
using namespace std;

int sumNeighbour(int x, int y, int a[][100], int m, int n) {
	const int direction[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
	int sum = 0;
	for(int i = 0; i < 8; i++) {
		int nx = x + direction[i][0];
		int ny = y + direction[i][1];
		if(nx >= 0 && nx < m && ny >= 0 && ny < n) sum+= a[nx][ny];
	}
	return sum;
}

int main()
{
    int m, n, k, q;
    cin >> m >> n >> k >> q;
    int a[100][100] = {0};   
    for(int i = 0; i < k; i++){
    	int x, y, v;
    	cin >> x >> y >> v;
    	a[x][y] = v;
	}
	
	for(int i = 0; i < q; i++){
		int x, y;
		cin >> x >> y;
		cout << sumNeighbour(x, y, a, m, n) << endl;
	}
    return 0;
}
