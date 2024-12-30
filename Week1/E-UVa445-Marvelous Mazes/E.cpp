#include <iostream>
#include <string>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("E.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    string ss;
    int charcnt = 0;
    char ch;
    while (getline(cin, ss)) {
        charcnt = 0;
        for (int i = 0; i < ss.size(); i++) {
            char& cur_ch = ss[i];
            if (isdigit(cur_ch)) charcnt += cur_ch - '0';
            else if (isupper(cur_ch) || cur_ch == '*' || cur_ch == 'b') {
                if (cur_ch == 'b') cur_ch = ' ';
                for (int j = 0; j < charcnt; j++) cout << cur_ch;
                charcnt = 0;
            }
            else if (cur_ch == '!') { cout << endl; charcnt = 0; }
        }
        cout << endl;
    }

    return 0;
}