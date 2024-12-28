#include <iostream>
#include <string>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("B.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    string ss;
    int charcnt = 0;
    char ch;
    while (getline(cin, ss)) {
        charcnt = 0;
        for (int i = 0; i < ss.size(); i++) {
            char& cur_ch = ss[i];
            if (isdigit(cur_ch)) {
                charcnt += cur_ch - '0';
            }
            else if ((cur_ch >= 'A' && cur_ch <= 'Z') || cur_ch == '*' || cur_ch == 'b') {
                if (cur_ch == 'b') cur_ch = ' ';
                for (int j = 0; j < charcnt; j++) putchar(cur_ch);
                charcnt = 0;
            }
            else if (cur_ch == '!') { putchar('\n'); charcnt = 0; }
        }
        putchar('\n');
    }

    return 0;
}