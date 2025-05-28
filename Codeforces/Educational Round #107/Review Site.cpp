#include <iostream>
using namespace std;

int solve() {
    int n;
    cin >> n;

    int res = 0;
    for (int i = 0; i < n; i++) {
        int r;
        cin >> r;

        if (r == 1 || r == 3) res++;
    }

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}
