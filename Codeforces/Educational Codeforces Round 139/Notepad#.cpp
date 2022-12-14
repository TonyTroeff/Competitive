#include <iostream>
#include <map>

using namespace std;

bool solve(const int &n, const string &s) {
    map<string, int> m;

    for (int i = 0; i < n - 1; i++) {
        string current = s.substr(i, 2);

        auto it = m.find(current);
        if (it != m.end()) {
            if (it->second < i - 1) return true;
        } else m[current] = i;
    }

    return false;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        string s;
        cin >> s;

        if (solve(n, s)) cout << "YES";
        else cout << "NO";

        cout << endl;
    }

    return 0;
}