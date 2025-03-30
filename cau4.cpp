
#include <iostream>
using namespace std;

int binarySearch (int a[], int size, int left, int right, int key) {
	if(left > right) {
		return -1;
	}
	
	int mid = (right + left)/2;
	if(a[mid] == key) return mid;
	
	else if(a[mid] > key) {
		return binarySearch(a, size, left, mid - 1, key);
	}
	
	else {
		return binarySearch(a, size, mid + 1, right, key);
	}
}

int main() {
	int n;
	cin >> n;
	
	int a[100];
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	
	int key;
	cin >> key;
	int res = binarySearch(a, n, 0, n - 1, key);
	if(res != -1) {
		cout << "Phan tu can tim co chi so la: " << res;
	}
	
	else cout << "Khong tim thay phan tu " << key;
	
}
