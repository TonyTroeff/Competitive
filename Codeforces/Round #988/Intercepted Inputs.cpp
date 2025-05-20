#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

pair<int, int> solve(const int &k, const vector<int> &a) {
    const int expected_product = k - 2;

    unordered_set<int> used;
    for (const int &num: a) {
        if (expected_product % num != 0) continue;

        int other = expected_product / num;
        if (used.contains(other)) return make_pair(other, num);

        used.insert(num);
    }

    return make_pair(0, 0);
}

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int k;
        cin >> k;

        vector<int> a(k);
        for (int &num: a) cin >> num;

        pair<int, int> ans = solve(k, a);
        cout << ans.first << ' ' << ans.second << endl;
    }
}
