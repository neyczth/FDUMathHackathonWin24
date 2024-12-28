#include <iostream>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("A.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int a, b;
    cin >> a >> b;
    cout << a+b << endl;

    return 0;
}