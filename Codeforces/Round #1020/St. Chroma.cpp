#include <iostream>
#include <vector>
using namespace std;

vector<int> solve() {
    int n, x;
    cin >> n >> x;

    vector<int> res(n);
    for (int i = 0; i < x; i++) res[i] = i;
    for (int j = x + 1; j < n; j++) res[j - 1] = j;

    if (x < n) res[n - 1] = x;

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        vector<int> res = solve();

        for (const int& el : res) cout << el << ' ';
        cout << endl;
    }
}