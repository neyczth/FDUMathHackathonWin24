#include <iostream>
#include <cstdint>
#define foreach(i, l, r) for (int i = l; i <= r; i++)
using namespace std;

// 数字码位数 | 第一位数字 | 第一位数字是否已经持续两个
// 是否有4 | 是否有8 | 是否已经有三连数字
uint64_t dp[15][15][2][2][2][2] = {0};

void update(const uint64_t& num_cnt, const uint64_t& first_num, const uint64_t &has_two_num,
            const uint64_t& has_4, const uint64_t& has_8, const uint64_t& has_triple,
            const uint64_t& next_num) {
    dp[num_cnt+1][next_num][next_num==first_num]
        [has_4 || next_num == 4][has_8 || next_num == 8]
        [has_triple || (next_num == first_num && has_two_num)]
    += dp[num_cnt][first_num][has_two_num][has_4][has_8][has_triple];
}

class Solver {
  public:    
    // 获取前缀固定下的答案数
    // pre - 前缀 | num_fix - 固定第 [0, num_fix) 位
    // 还有 [num_fix, 10] 要处理, 共 10-num_fix+1 位
    uint64_t get_ans_fix_pre(uint64_t pre, const uint64_t &num_fix) {
        uint64_t last_num = pre%10, last_second_num = pre/10%10;
        bool has_two_num = (last_num == last_second_num);
        bool has_4 = false, has_8 = false, has_triple = false;

        // 处理前缀信息
        if (num_fix > 0) {
            uint64_t last_num = pre%10;
            uint64_t last_num_cnt = 1;
            if (pre%10 == 4) has_4 = true;
            if (pre%10 == 8) has_8 = true;
            pre /= 10;
            for (uint64_t i = 1; i < num_fix; i++) {
                uint64_t cur_num = pre%10; pre /= 10;
                if (cur_num == last_num) last_num_cnt++;
                else last_num = cur_num, last_num_cnt = 1;
                if (cur_num == 4) has_4 = true;
                if (cur_num == 8) has_8 = true;
                if (last_num_cnt >= 3) has_triple = true;
            }
        }

        if (has_4 && has_8) return 0;
        if (num_fix == 11) return has_triple;
        uint64_t ans = 0;

        // 枚举后缀
        foreach(first_num, 0, 9)
        foreach(i, 0, 1)  // 首个数字是否连续出现两次
        foreach(j, 0, 1)  // 是否有4
        foreach(k, 0, 1)  // 是否有8
        foreach(l, 0, 1)  // 是否已经有三连数
        {
            const bool has_triple_tmp = has_triple || l || (first_num == last_num && (i || has_two_num));
            const bool has_4_tmp = has_4 || j;
            const bool has_8_tmp = has_8 || k;
            if (has_4_tmp && has_8_tmp) continue;
            if (has_triple_tmp) ans += dp[11-num_fix][first_num][i][j][k][l];
        }

        return ans;
    }

    // 获取 [1e10, R] 之间的合法个数
    // 特殊: R = 1e10-1 输出 0, 避免边界溢出
    uint64_t get_answer(uint64_t R) {
        if (R == 9999999999) return get_ans_fix_pre(0, 1);

        uint64_t ans = 0;
        int u_bound[15] = {0};
        uint64_t pre = 0;
        for (int i = 10; i >= 0; i--) { u_bound[i] = R % 10; R /= 10; }

        // 固定[0, fix_cnt), 枚举fix_cnt位搜索答案
        for (int fix_cnt = 0; fix_cnt < 11; fix_cnt++) {
            for (int cur_num = 0; cur_num < u_bound[fix_cnt]; cur_num++)
                ans += get_ans_fix_pre(pre*10 + cur_num, fix_cnt+1);
            pre = pre*10 + u_bound[fix_cnt];
        }
        return ans + get_ans_fix_pre(pre, 11);
    }

};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("R.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    // 先统计通用答案
    // 初始化
    foreach(i, 0, 9) dp[1][i][0][i==4][i==8][0] = 1;

    // "我为人人" 式更新
    foreach(num_cnt, 1, 9)
    foreach(first_num, 0, 9)
    foreach(has_two_num, 0, 1)
    foreach(has_4, 0, 1)
    foreach(has_8, 0, 1)
    foreach(has_triple, 0, 1)
    foreach(next_num, 0, 9)
        update(num_cnt, first_num, has_two_num, has_4, has_8, has_triple, next_num);

    Solver solver;
    uint64_t L, R;
    cin >> L >> R;
    cout << solver.get_answer(R) - solver.get_answer(L-1) << endl;
    return 0;
}