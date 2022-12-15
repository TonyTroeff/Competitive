#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool solve(const vector<int> &a) {
    set<int> s;

    for (int el : a) {
        if (s.find(el) != s.end()) return false;
        s.insert(el);
    }

    return true;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        if (solve(a)) cout << "YES";
        else cout << "NO";
        cout << endl;
    }
}