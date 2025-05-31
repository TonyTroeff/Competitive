#include <iostream>
using namespace std;

bool solve() {
    int n;
    cin >> n;

    return n % 2 != 0;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << (solve() ? "YES" : "NO") << endl;
}