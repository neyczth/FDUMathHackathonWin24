#include <iostream>
#include <algorithm>
using namespace std;

int map_size, tot_time;

class Rabbit {
  public:
    int x = 0, y = 0, velocity = 0;
    char direction = 'N';
    int turn_left_period = 0, time_left_to_turn = 0;

    void init(const int &_x, const int &_y) {
        x = _x; y = _y;
        cin >> direction >> velocity >> turn_left_period;
        if (map_size > 1) velocity %= 2 * (map_size-1);
        time_left_to_turn = turn_left_period;
    }

    void move() {
        switch (direction) {
            case 'N':
                x -= velocity;
                if (x < 1) x = 2 - x, direction = 'S';
                if (x > map_size) x = 2*map_size - x, direction = 'N';
                break;
            case 'W':
                y -= velocity;
                if (y < 1) y = 2 - y, direction = 'E';
                if (y > map_size) y = 2*map_size - y, direction = 'W';
                break;
            case 'S':
                x += velocity;
                if (x > map_size) x = 2*map_size - x, direction = 'N';
                if (x < 1) x = 2 - x, direction = 'S';
                break;
            case 'E':
                y += velocity;
                if (y > map_size) y = 2*map_size - y, direction = 'W';
                if (y < 1) y = 2 - y, direction = 'E';
                break;
        }
        time_left_to_turn--;
        if (time_left_to_turn == 0)
            time_left_to_turn = turn_left_period;
    }

    void check_turn_left() {
        if (time_left_to_turn < turn_left_period) return;
        switch (direction) {
            case 'N': direction = 'W'; break;
            case 'W': direction = 'S'; break;
            case 'S': direction = 'E'; break;
            case 'E': direction = 'N'; break;
        }
    }

    void print_cur_pos() {
        cout << x << ' ' << y << endl;
    }
};
Rabbit rabbit_1, rabbit_2;

inline bool is_meet(const Rabbit &a, const Rabbit &b) {
    return a.x == b.x && a.y == b.y;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("O.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    while (cin >> map_size) {
        if (!map_size) break;
        rabbit_1.init(1, 1); rabbit_2.init(map_size, map_size);
        cin >> tot_time;
        while (tot_time--) {
            rabbit_1.move();
            rabbit_2.move();
            if (is_meet(rabbit_1, rabbit_2))
                swap(rabbit_1.direction, rabbit_2.direction);
            else {
                rabbit_1.check_turn_left();
                rabbit_2.check_turn_left();
            }
        }
        rabbit_1.print_cur_pos();
        rabbit_2.print_cur_pos();
    }

    return 0;
}