// Problem C
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("C.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    string str1, str2;
    getline(cin, str1); getline(cin, str2);
    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

    auto res = str1.compare(str2);
    if      (res < 0)   cout << "-1" << endl;
    else if (res == 0)  cout <<  "0" << endl;
    else                cout <<  "1" << endl;

    return 0;
}