#include <iostream>
using namespace std;

bool solve() {
    string s;
    cin >> s;

    int balance = 0;
    for (int i = 1; i < s.size() - 1; i++) {
        if (s[i] == '(') balance++;
        else if (s[i] == ')' && --balance < 0) return true;
    }

    return balance != 0;
}

int main() {
    int t;
    cin >> t;

    while (t--)
        cout << (solve() ? "YES" : "NO") << endl;
}