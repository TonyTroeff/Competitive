#include <iostream>
#include <vector>
using namespace std;

int solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &el: a) cin >> el;

    int res = 0, index = 0;
    while (index < n) {
        const int start = index;
        while (index + 1 < n && a[start] + 1 >= a[index + 1]) {
            index++;
        }

        res++;
        index++;
    }

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
