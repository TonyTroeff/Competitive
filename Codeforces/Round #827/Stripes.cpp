#include <iostream>
#include <vector>

using namespace std;

#define N 8

char solve(const vector<string> &a) {
    for (const string &row : a) {
        bool isFull = true;
        for (int i = 0; isFull && i < N; i++) {
            if (row[i] != 'R') isFull = false;
        }

        if (isFull) return 'R';
    }

    for (int colIndex = 0; colIndex < N; colIndex++) {
        bool isFull = true;
        for (int i = 0; isFull && i < N; i++) {
            if (a[i][colIndex] != 'B') isFull = false;
        }

        if (isFull) return 'B';
    }

    return 0;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        vector<string> a(N);
        for (auto &el: a) cin >> el;

        cout << solve(a) << endl;
    }
}