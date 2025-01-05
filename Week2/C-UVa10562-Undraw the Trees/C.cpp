#include <iostream>
#include <cstring>
#define MAXN 210
using namespace std;

char ss[MAXN];
char str_map[MAXN][MAXN];

void reset_map() {
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            str_map[i][j] = ' ';
}

void print(const int& r, const int& c) {
    cout << str_map[r][c] << "(";
    if (str_map[r+1][c] == '|') {
        int left = c, right = c;
        while (left > 0 && str_map[r+2][left-1] == '-') left--;
        while (str_map[r+2][right+1] == '-') right++;
        for (int k = left; k <= right; k++)
            if (str_map[r+3][k] != ' ' && str_map[r+3][k] != '\0') print(r+3, k);
    }
    cout << ")";
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("C.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int num_case;
    cin >> num_case;
    cin.getline(ss, MAXN);
    while (num_case--) {
        reset_map();
        int row_idx = 0;
        while (cin.getline(ss, MAXN)) {
            if (strcmp(ss, "#") == 0) break;
            strcpy(str_map[row_idx++], ss);
        }

        if (row_idx == 0) { cout << "()" << endl; continue; }

        int root_r = 0, root_c = 0;
        while (str_map[root_r][root_c] == ' ') root_c++;
        cout << "(";
        print(root_r, root_c);
        cout << ")" << endl;
    }

    return 0;
}