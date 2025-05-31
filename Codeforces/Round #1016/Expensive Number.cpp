#include <iostream>
using namespace std;

int solve() {
    string n;
    cin >> n;

    int skippable_zeros = 0, total_zeros = 0;
    for (const char& d : n) {
        if (d == '0') total_zeros++;
        else skippable_zeros = total_zeros;
    }

    return static_cast<int>(n.size()) - skippable_zeros - 1;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
