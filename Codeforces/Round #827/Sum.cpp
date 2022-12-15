#include <iostream>
using namespace std;

bool solve(const int &a, const int &b, const int &c) {
    return a + b == c || b + c == a || a + c == b;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;

        if (solve(a, b, c)) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
}