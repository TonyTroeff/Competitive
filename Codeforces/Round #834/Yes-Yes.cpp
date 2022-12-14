#include <iostream>
#include <string>
using namespace std;

const string yes = "Yes";

bool solve(const string& s) {
    string::size_type yesIndex = yes.find(s[0]);
    if (yesIndex == -1) return false;

    for (char l : s) {
        if (l != yes[yesIndex]) return false;
        yesIndex = (yesIndex + 1) % 3;
    }

    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        if (solve(s)) cout << "YES";
        else cout << "NO";

        cout << endl;
    }

    return 0;
}
