#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int solve(const vector<int> &a) {
    unordered_map<int, int> counter;
    for (const int &num: a) counter[num]++;

    int ans = 0;
    for (const pair<const int, int> &el: counter) ans += el.second / 2;

    return ans;
}

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int j = 0; j < n; j++) cin >> a[j];

        cout << solve(a) << endl;
    }
}
