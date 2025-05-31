#include <iostream>
using namespace std;

void solve() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    cout << (min(a, c) < min(b, d) ? "Flower" : "Gellyfish") << endl;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        solve();
}
