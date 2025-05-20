#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

pair<int, int> solve(const int& n, const vector<int> &a) {
    int on = 0;
    for (const int& el : a) {
        if (el == 1) on++;
    }

    return make_pair(on % 2, on > n ? 2 * n - on : on);
}

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<int> a(2 * n);
        for (int& el: a) cin >> el;

        auto [min, max] = solve(n, a);
        cout << min << ' ' << max << endl;
    }
}
