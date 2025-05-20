#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int temp;
        for (int i = 0; i < n; i++) cin >> temp;
        cout << 1 << ' ' << n << endl;
    }

    return 0;
}