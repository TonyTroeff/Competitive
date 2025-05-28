#include <iostream>
#include <ranges>
#include <unordered_map>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    unordered_map<int, int> m;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;

        if (!m.contains(a))
            m[a] = i;
    }

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;

        cout << m[t] + 1 << ' ';

        for (auto& value: views::values(m)) {
            if (value < m[t]) ++value;
        }

        m[t] = 0;
    }

    cout << endl;
}
