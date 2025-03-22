#include <iostream>

using namespace std;

int my_strlen(char *c) {
    int length = 0;
    while(c[length] != '\0') {
        length++;
    }
    return length;
}

char* my_strcpy(char a[]) {
    int n = my_strlen(a);
    char* new_str = new char[n + 1];
    for (int i = 0; i < n; i++) new_str[i] = a[i];
    new_str[n] = '\0';
    return new_str;
}

char *my_reverse(char c[]) {
    int length = my_strlen(c);
    for(int i = 0; i < length / 2; i++) {
        swap(c[i], c[length - i - 1]);
    }
    return c;
}

char* my_delete(char a[], char c) {
    int length = my_strlen(a);
    int j = 0;
    for(int i = 0; i < length; i++) {
        if(a[i] != c) {
            a[j] = a[i];
            j++;
        }
    }
    a[j] = '\0';
    return a;
}

char* pad_right(char a[], int n) {
    int length = my_strlen(a);
    if(length < n) {
        for(int i = length; i < n; i++) {
            a[i] = ' ';
        }
        a[n] = '\0';
    }
    return a;
}

char* pad_left(char a[], int n) {
    int length = my_strlen(a);
    if (length >= n) {
        return my_strcpy(a);
    }

    int space = n - length;
    char* new_str = new char[n + 1];

    for (int i = 0; i < space; i++) {
        new_str[i] = ' ';
    }
    for (int i = 0; i <= length; i++) {
        new_str[i + space] = a[i];
    }
    new_str[n] = '\0';

    return new_str;
}

char* truncate(char a[], int n) {
    int length = my_strlen(a);
    if(length <= n) return a;

    a[n] = '\0';
    return a;
}

bool is_palindrome(char a[]) {
    int length = my_strlen(a);
    for(int i = 0; i < length/2; i++) {
        if (a[i] != a[length - i - 1]) {
            return false;
        }
    }
    return true;
}

char* trim_left(char a[]) {
    int start = 0;
    while (a[start] == ' ') {
        start++;
    }
    if (start == 0) return a;
    int i = 0;
    while (a[start] != '\0') {
        a[i] = a[start];
        i++;
        start++;
    }
    a[i] = '\0';

    return a;
}

char* trim_right(char a[]) {
    int length = my_strlen(a);
    int last_non_space = length - 1;
    while (last_non_space >= 0 && a[last_non_space] == ' ') {
        last_non_space--;
    }
    a[last_non_space + 1] = '\0';

    return a;
}

int main()
{
    char c[] = "Hello";
    char c1[] = "How are you";
    char c2[] = "Hanoi";
    char c3[] = "abcxyzghi";
    char c4[] = "madam";
    char c5[] = "    Mask on";
    char c6[] = "Fire in the hole    ";
    cout << c << endl;
    cout << my_reverse(c) << endl;
    cout << my_delete(c1, 'l') << endl;
    cout << "/" << pad_left(c2, 10) << "/" << endl;
    cout << "/" << pad_right(c2, 10) << "/" << endl;
    cout << truncate(c3, 5) << endl;
    cout << is_palindrome(c4) << endl;
    cout << trim_left(c5) << endl;
    cout << trim_right(c6) << endl;
    return 0;
}
