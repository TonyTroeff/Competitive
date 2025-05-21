#include <iostream>
using namespace std;

int solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int res = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') res += n - 1;
        else res++;
    }

    return res;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << solve() << endl;
}