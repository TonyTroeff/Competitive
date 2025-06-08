#include <iostream>
using namespace std;

int solve() {
    int x;
    cin >> x;

    int power = 0, mult = 1;
    while (mult <= x) {
        power++;
        mult *= 2;
    }

    return 2 * power + 1;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}