#include <iostream>
using namespace std;

bool solve(const int &n, const string &a, const string &b) {
    int rectSequence = 0, prevSingleCellRow = -1;
    for (int i = 0; i < n; i++) {
        if (a[i] == 'B' && b[i] == 'B') rectSequence++;
        else {
            int currentSingleCellRow = a[i] == 'B' ? 0 : 1;

            if (prevSingleCellRow != -1) {
                bool sameRow = currentSingleCellRow == prevSingleCellRow;
                bool evenSequence = rectSequence % 2 == 0;
                if (sameRow != evenSequence) return false;
            }

            rectSequence = 0;
            prevSingleCellRow = currentSingleCellRow;
        }
    }

    return true;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        string a, b;
        cin >> a >> b;

        if (solve(n, a, b)) cout << "YES";
        else cout << "NO";

        cout << endl;
    }

    return 0;
}