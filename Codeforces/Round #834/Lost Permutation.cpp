#include <iostream>
using namespace std;

bool solve(int s, int max) {
    int n = 1;
    while (s > 0) s -= n++;

    return s == 0 && n > max;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int m, s;
        cin >> m >> s;

        int max = 0;
        for (int i = 0; i < m; i++) {
            int el;
            cin >> el;

            if (el > max) max = el;
            s += el;
        }

        if (solve(s, max)) cout << "YES";
        else cout << "NO";

        cout << endl;
    }

    return 0;
}
