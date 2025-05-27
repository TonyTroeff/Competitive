#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

vector<int> solve() {
    int year;
    cin >> year;

    const double r1 = sqrt(year);
    const int r2 = static_cast<int>(r1);
    if (r1 == r2) return {0, r2};

    return {-1};
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        const vector<int> res = solve();
        for (const int &el: res) cout << el << ' ';
        cout << endl;
    }
}
