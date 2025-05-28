#include <iostream>
using namespace std;

bool solve() {
    int a, b, c;
    cin >> a >> b >> c;

    const int sum = a + b + c;
    if (sum % 3 != 0) return false;

    const int norm = sum / 3;
    return a <= norm && b <= norm;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        if (solve()) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}
