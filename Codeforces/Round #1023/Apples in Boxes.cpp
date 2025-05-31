#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

string solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    ranges::sort(a);

    int fixes = 1;
    for (int i = n - 1; i >= 0; i--) {
        const int diff = a[i] - a[0];
        if (diff > k) {
            if (diff == k + 1 && fixes > 0) fixes--;
            else return "Jerry";
        }
    }

    int sum = 0;
    for (const int& el: a) sum += el;

    return sum % 2 == 0 ? "Jerry" : "Tom";
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
