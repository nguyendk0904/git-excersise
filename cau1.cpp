
#include <iostream>
using namespace std;


int main()
{
    int n, k;
    cin >> n;
    
    int a[1000];
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    cin >> k;
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[i] + a[j] == k) {
                cout << a[i] << " " << a[j];
            }
        }
        cout << endl;
    }
    
    
    return 0;
}
