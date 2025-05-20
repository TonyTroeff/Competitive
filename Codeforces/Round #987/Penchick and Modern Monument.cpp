#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int solve(const int &n, const vector<int> &h) {
    int index = 0, max_length = 0;

    while (index < n) {
        const int start = index;
        while (index + 1 < n && h[index + 1] == h[index]) index++;

        max_length = max(max_length, index - start + 1);
        index++;
    }

    return n - max_length;
}

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<int> h(n);
        for (int &num: h) cin >> num;

        cout << solve(n, h) << endl;
    }
}
