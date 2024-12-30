#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Puzzle {
  public:
    char puzzle_map[5][5] = {0};
    int cur_x = 0, cur_y = 0;

    void set_cur_pos(const int &x, const int &y) {
        cur_x = x; cur_y = y;
    }

    bool is_in_map(const int &x, const int &y) {
        return x >= 0 && x < 5 && y >= 0 && y < 5;
    }

    bool move(const int &dx, const int &dy) {
        int&& new_x = cur_x+dx, new_y = cur_y + dy;
        if (!is_in_map(new_x, new_y)) return false;

        puzzle_map[cur_x][cur_y] = puzzle_map[new_x][new_y];
        puzzle_map[new_x][new_y] = ' ';
        cur_x = new_x; cur_y = new_y;
        return true;
    }

    void print() {
        for (int i = 0; i < 5; i++) {
            cout << puzzle_map[i][0];
            for (int j = 1; j < 5; j++) cout << ' ' << puzzle_map[i][j];
        }
    }
};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("G.in", "r", stdin);
    #endif

    string ss;
    Puzzle puzzle;
    int test_cnt = 0;
    while (1) {
        test_cnt++;
        getline(cin, ss);
        if (ss == "Z") break;
        for (int j = 0; j < 5; j++) {
            puzzle.puzzle_map[0][j] = ss[j];
            if (ss[j] == ' ') puzzle.set_cur_pos(0, j);
        }
        for (int i = 1; i < 5; i++) {
            getline(cin, ss);
            for (int j = 0; j < 5; j++) {
                puzzle.puzzle_map[i][j] = ss[j];
                if (ss[j] == ' ') puzzle.set_cur_pos(i, j);
            }
        }

        bool is_ok = true;
        string op_list = "";
        char ch;
        while ((ch = getchar()) != '0') {
            if (ch == 'A' || ch == 'B' || ch == 'L' || ch == 'R') op_list += ch;
        }
        for (auto& ch : op_list) {
            // A - up | B - down | L - left | R - right | O - end
            int dx = 0, dy = 0;
            switch (ch) {
                case 'A': dx = -1, dy =  0; break;
                case 'B': dx =  1, dy =  0; break;
                case 'L': dx =  0, dy = -1; break;
                case 'R': dx =  0, dy =  1; break;
            }
            is_ok = puzzle.move(dx, dy);
            if (!is_ok) break;
        }

        if (test_cnt > 1) cout << endl;
        cout << "Puzzle #" << test_cnt << ':' << endl;
        if (!is_ok) cout << "This puzzle has no final configuration." << endl;
        else puzzle.print();

        getline(cin, ss);
    }
    cout << endl;

    return 0;
}