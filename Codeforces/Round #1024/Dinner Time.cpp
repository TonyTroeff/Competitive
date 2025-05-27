#include <iostream>
using namespace std;

bool solve() {
    int n, m, p, q;
    cin >> n >> m >> p >> q;

    return n % p != 0 || n / p * q == m;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << (solve() ? "YES" : "NO") << endl;
}
