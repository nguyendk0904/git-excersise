#include <iostream>
using namespace std;

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  
    }
}

int main() {
	int a[6] = {1, 4, 19, 0, -2, 13};
	bubbleSort(a, 6);
	for(int i = 0; i < 6; i++) {
		cout << a[i] << " ";
	}
	
	return 0;
}

/*
- Uu diem: thuat toan don gian, de cai dat, on dinh
- Nhuoc diem: 
	Toc do cham khi mang co kich thuoc lon
	Selection sort co so lan hoan doi it hon Bubble sort 
	Trong truong hop mang gan nhu duoc sap xep thi Insertion sort hieu qua hon Bubble sort

*/

