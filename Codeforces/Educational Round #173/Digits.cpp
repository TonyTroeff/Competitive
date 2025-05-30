#include <iostream>
#include <vector>
using namespace std;

vector<int> solve() {
    int n, d;
    cin >> n >> d;

    vector<int> res;

    res.push_back(1);
    if (d % 3 == 0 || n >= 3) res.push_back(3);
    if (d == 5) res.push_back(5);
    if (d == 7 || n >= 3) res.push_back(7);
    if (d == 9 || n >= 6 || (n >= 3 && d % 3 == 0)) res.push_back(9);

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        const vector<int> res = solve();
        for (const int& el : res) cout << el << ' ';
        cout << endl;
    }
}