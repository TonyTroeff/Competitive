#include <iostream>
using namespace std;

int solve(int l, int r, int x, int a, int b) {
    if (a == b) return 0;
    if (abs(a - b) >= x) return 1;
    if (r - max(a, b) >= x || min(a, b) - l >= x) return 2;
    if ((r - b >= x && a - l >= x) || (b - l >= x && r - a >= x)) return 3;
    return -1;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int l, r, x;
        cin >> l >> r >> x;

        int a, b;
        cin >> a >> b;

        int minOperations = solve(l, r, x, a, b);
        cout << minOperations << endl;
    }

    return 0;
}