#include <iostream>
#include <string>
#include <algorithm>

class Puzzle {
    // 一个维护迷宫的类, 实现迷宫的存储和一些基本功能.
  public:
    char puzzle_map[5][5] = {0};  // 迷宫地图
    int cur_x = 0, cur_y = 0;     // 空位的位置

    void set_cur_pos(const int &x, const int &y) {
        // 记录迷宫空位的当前位置为 (x, y)
        cur_x = x; cur_y = y;
    }

    bool is_in_map(const int &x, const int &y) {
        // Return: bool, 点 (x, y) 是否在迷宫地图范围内
        return x >= 0 && x < 5 && y >= 0 && y < 5;
    }

    bool move(const int &dx, const int &dy) {
        // 将空位从当前位置挪动 (dx, dy)
        // 即 (cur_x, cur_y) -> (cur_x + dx, cur_y + dy)
        // 对合法操作, 修改地图信息并返回 true; 对不合法的操作, 返回 false.
        // Return: bool, 此移动是否合法 (即是否走出了迷宫范围)
        int&& new_x = cur_x + dx, new_y = cur_y + dy;
        if (!is_in_map(new_x, new_y)) return false;

        puzzle_map[cur_x][cur_y] = puzzle_map[new_x][new_y];
        puzzle_map[new_x][new_y] = ' ';
        cur_x = new_x; cur_y = new_y;
        return true;
    }

    void print() {
        // 打印迷宫
        for (int i = 0; i < 5; i++) {
            std::cout << puzzle_map[i][0];
            for (int j = 1; j < 5; j++) std::cout << ' ' << puzzle_map[i][j];
            std::cout << std::endl;
        }
    }
};

class PuzzleProblemSolver {
    // 一个求解本题迷宫问题的求解器类
  public:
    Puzzle puzzle;        // 迷宫
    std::string op_list;  // 记录操作序列

    bool input() {
        // 读入一个迷宫的地图
        // Return: bool, 返回值为 false 表示输入结束.
        std::string ss;
        getline(std::cin, ss);
        if (ss == "Z") return false;  // 输入结束
        
        for (int j = 0; j < 5; j++) {
            puzzle.puzzle_map[0][j] = ss[j];
            if (ss[j] == ' ') puzzle.set_cur_pos(0, j);
        }
        for (int i = 1; i < 5; i++) {
            getline(std::cin, ss);
            for (int j = 0; j < 5; j++) {
                puzzle.puzzle_map[i][j] = ss[j];
                if (ss[j] == ' ') puzzle.set_cur_pos(i, j);
            }
        }

        return true;
    }

    void get_op_list() {
        // 读入当前测试数据的所有操作.
        op_list.clear();
        std::string ss;
        char ch;
        while (std::cin >> ch) {
            if (ch == '0') break;
            if (ch == 'A' || ch == 'B' || ch == 'L' || ch == 'R') op_list += ch;
        }
        getline(std::cin, ss);  // 吞掉行末多余空格和换行符
    }

    bool move() {
        // 对当前迷宫执行操作序列中的所有操作.
        // Return: bool, 指示当前迷宫的操作序列是否完全合法.
        for (auto& ch : op_list) {
            // A - up | B - down | L - left | R - right
            int dx = 0, dy = 0;
            switch (ch) {
                case 'A': dx = -1, dy =  0; break;
                case 'B': dx =  1, dy =  0; break;
                case 'L': dx =  0, dy = -1; break;
                case 'R': dx =  0, dy =  1; break;
            }
            if(!puzzle.move(dx, dy)) return false;
        }
        return true;
    }

    void print_no_figuration() {
        // 打印操作不合法时的信息
        std::cout << "This puzzle has no final configuration." << std::endl;
    }

    void print_puzzle() {
        // 打印迷宫地图
        puzzle.print();
    }
};

void print_solution_title(const int &test_cnt) {
    if (test_cnt > 1) std::cout << std::endl;
    std::cout << "Puzzle #" << test_cnt << ':' << std::endl;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("G.in", "r", stdin);
    #endif

    PuzzleProblemSolver solver;
    int test_cnt = 0;
    while (solver.input()) {
        print_solution_title(++test_cnt);
        solver.get_op_list();
        if (!solver.move()) solver.print_no_figuration();
        else solver.print_puzzle();
    }

    return 0;
}