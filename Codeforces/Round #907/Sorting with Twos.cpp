#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

bool solve(const vector<int> &a) {
    int endOfCurrentChunk = 1, iterationIndex = 0;
    bool isFirstInChunk = true;

    while (iterationIndex < a.size()) {
        if (iterationIndex == endOfCurrentChunk) {
            endOfCurrentChunk *= 2;
            isFirstInChunk = true;
        }

        if (!isFirstInChunk && a[iterationIndex - 1] > a[iterationIndex]) return false;

        iterationIndex++;
        if (isFirstInChunk) isFirstInChunk = false;
    }

    return true;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int j = 0; j < n; j++) cin >> a[j];

        bool ans = solve(a);
        cout << (ans ? "YES": "NO") << endl;
    }
}