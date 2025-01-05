#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <stack>
using namespace std;

struct Intersection {
    int direction = 0, x = 0, y = 0;
    int last_d = 0, last_x = 0, last_y = 0;
    vector<int> next_direction;
    bool vst = false;

    Intersection(const int& _d=0, const int& _x=0, const int& _y=0):
        direction(_d), x(_x), y(_y) {}
};
Intersection inter_list[4][10][10];
Intersection start, endpos;

void init_inter_list() {
    for (int d = 0; d < 4; d++) {
        for (int x = 1; x <= 9; x++) {
            for (int y = 1; y <= 9; y++) {
                inter_list[d][x][y].direction = d;
                inter_list[d][x][y].x = x;
                inter_list[d][x][y].y = y;
                inter_list[d][x][y].vst = false;
                inter_list[d][x][y].next_direction.clear();
            }
        }
    }
}

// Directions: 0 - (0, 1) E | 1 - (1, 0) S | 2 - (0, -1) W | 3 - (-1, 0) N
map<char, int> direction_idx{ {'E', 0}, {'S', 1}, {'W', 2}, {'N', 3} };
inline int get_turn_left_direction (const int& x) { return (x+3)%4; }
inline int get_turn_right_direction(const int& x) { return (x+1)%4; }

// 从cur向direction方向走的下一个交叉口信息
Intersection get_next_intersection(const Intersection& cur, const int& direction) {
    int dx = 0, dy = 0;
    switch (direction) {
        case 0: dx =  0, dy =  1; break;
        case 1: dx =  1, dy =  0; break;
        case 2: dx =  0, dy = -1; break;
        case 3: dx = -1, dy =  0; break;
    }
    return Intersection(direction, cur.x+dx, cur.y+dy);
}

bool is_in_map(const Intersection& inter) {
    const int& x = inter.x, y = inter.y;
    return x >= 1 && x <= 9 && y >= 1 && y <= 9;
}

int bfs() {
    queue<Intersection> q;
    q.push(inter_list[start.direction][start.x][start.y]);
    inter_list[start.direction][start.x][start.y].vst = true;
    while (!q.empty()) {
        Intersection now = q.front(); q.pop();
        for (auto& d : now.next_direction) {
            Intersection next_pos = get_next_intersection(now, d);
            if (!is_in_map(next_pos)) continue;
            Intersection &next_iter = inter_list[next_pos.direction][next_pos.x][next_pos.y];
            if (!next_iter.vst) {
                next_iter.vst = true;
                next_iter.last_x = now.x;
                next_iter.last_y = now.y;
                next_iter.last_d = now.direction;
                q.push(next_iter);
            }

            if (next_iter.x == endpos.x && next_iter.y == endpos.y) return next_iter.direction;
        }
    }
    return -1;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("B.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    string case_name, direction_list, ss;
    int x, y;
    char start_direction;
    while (getline(cin, case_name)) {
        if (case_name == "END") break;

        init_inter_list();

        cin >> start.x >> start.y >> start_direction >> endpos.x >> endpos.y;
        start.direction = direction_idx[start_direction];
        inter_list[start.direction][start.x][start.y].next_direction.push_back(start.direction);
        while (true) {
            cin >> x;
            if (!x) break;
            cin >> y;
            while (cin >> direction_list) {
                if (direction_list == "*") break;
                int& direction = direction_idx[direction_list[0]];
                for (int i = 1; i < direction_list.size(); i++) {
                    int tmp_direction = 0;
                    switch (direction_list[i]) {
                        case 'F': tmp_direction = direction; break;
                        case 'L': tmp_direction = get_turn_left_direction(direction); break;
                        case 'R': tmp_direction = get_turn_right_direction(direction); break;
                    }
                    inter_list[direction][x][y].next_direction.push_back(tmp_direction);
                }
            }
        }

        // BFS
        int res_direction = bfs();

        cout << case_name;
        if (res_direction == -1) cout << endl << "  No Solution Possible" << endl;
        else {
            stack<Intersection> st;
            int x = endpos.x, y = endpos.y, direction = res_direction;
            st.push(inter_list[direction][x][y]);
            while (x != start.x || y != start.y) {
                Intersection& cur_inter = inter_list[direction][x][y];
                x = cur_inter.last_x; y = cur_inter.last_y; direction = cur_inter.last_d;
                st.push(inter_list[direction][x][y]);
            }
            int print_cnt = 0;
            while (!st.empty()) {
                Intersection& cur = st.top(); st.pop();
                if (print_cnt%10 == 0) cout << endl << "  ";
                else cout << ' ';
                cout << "(" << cur.x << "," << cur.y << ")";
                print_cnt++;
            }
            cout << endl;
        }
        getline(cin, ss);
    }

    return 0;
}