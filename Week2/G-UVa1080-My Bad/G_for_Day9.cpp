#include <cstdio>
#include <cstring>
#define MAX_NUM_INPUTS    10
#define MAX_NUM_GATES     25
#define MAX_NUM_OUTPUTS   25
#define MAX_NUM_BEHAVIOR 260
using namespace std;

class Gate {
  public:
    char gate_type = ' ';         // 门的类型, a - and | o - or | x - xor | n - not
    int fail_type = 0;            // 失效类型, 0 - inverted | 1 - stuck at 0 | 2 - stuck at 1
    bool is_from_input[2] = {0};  // 门的两个输入来源: 1 - 输入 | 0 - 其他门
    int input_idx[2] = {0};       // 门的两个输入的下标
    bool vst = 0;                 // 是否访问过
    bool output = 0;              // 输出值, 用于记忆化搜索
};

class Solver {
  public:
    Gate gates[MAX_NUM_GATES];
    int num_inputs, num_gates, num_outputs, num_behaviors;
    int output_idx[MAX_NUM_OUTPUTS] = {0};                          // 各输出的下标
    bool behavior_input[MAX_NUM_BEHAVIOR][MAX_NUM_INPUTS] = {0};    // 各behavior的输入
    bool expected_output[MAX_NUM_BEHAVIOR][MAX_NUM_OUTPUTS] = {0};  // 各behavior的预期输出
    static const char* fail_info_str[];

    /**
     * @brief 读取输入
     * 
     * @return true  读取成功
     * @return false 输入数据结束
     */
    bool input() {
        scanf("%d %d %d", &num_inputs, &num_gates, &num_outputs);
        if (!num_inputs && !num_gates && !num_outputs) return false;

        char input_type;
        for (int i = 1; i <= num_gates; i++) {
            Gate &cur_gate = gates[i];
            scanf(" %c", &cur_gate.gate_type);
            scanf(" %c%d", &input_type, &cur_gate.input_idx[0]);
            cur_gate.is_from_input[0] = (input_type == 'i');
            if (cur_gate.gate_type != 'n') {
                scanf(" %c%d", &input_type, &cur_gate.input_idx[1]);
                cur_gate.is_from_input[1] = (input_type == 'i');
            }
        }

        for (int i = 0; i < num_outputs; i++) scanf("%d", &output_idx[i]);
        
        scanf("%d", &num_behaviors);
        for (int i = 0; i < num_behaviors; i++) {
            for (int j = 1; j <= num_inputs; j++) scanf("%d", &behavior_input[i][j]);
            for (int j = 0; j < num_outputs; j++) scanf("%d", &expected_output[i][j]);
        }
        return true;
    }

    /**
     * @brief 获取指定behavior下指定门的输出
     * 
     * @param behavior_idx behavior的下标
     * @param gate_idx     门的下标
     * @param fail_idx     失效门的下标
     * @param fail_type    失效类型
     */
    bool get_output(const int& behavior_idx, const int &gate_idx, const int& fail_idx=0, const int& fail_type=0) {
        Gate &cur_gate = gates[gate_idx];
        if (cur_gate.vst) return cur_gate.output;

        cur_gate.vst = 1;
        if (fail_idx == gate_idx) {
            switch (fail_type) {
                case 1: cur_gate.output = 0; return 0; break;
                case 2: cur_gate.output = 1; return 1; break;
            }
        }

        bool input0 = 0, input1 = 0;
        if (cur_gate.is_from_input[0])
            input0 = behavior_input[behavior_idx][cur_gate.input_idx[0]];
        else input0 = get_output(behavior_idx, cur_gate.input_idx[0], fail_idx, fail_type);
        if (cur_gate.gate_type != 'n') {
            if (cur_gate.is_from_input[1]) input1 = behavior_input[behavior_idx][cur_gate.input_idx[1]];
            else input1 = get_output(behavior_idx, cur_gate.input_idx[1], fail_idx, fail_type);
        }
        bool ans;
        switch (cur_gate.gate_type) {
            case 'a': ans = input0 & input1; break;
            case 'o': ans = input0 | input1; break;
            case 'x': ans = input0 ^ input1; break;
            case 'n': ans = !input0;         break;
        }
        if (fail_idx == gate_idx && fail_type == 0) ans ^= 1;
        cur_gate.output = ans;
        return ans;
    }

    void reset_vst() {
        for (int i = 1; i <= num_gates; i++) gates[i].vst = 0;
    }

    /**
     * @brief 检查对所有behavior, 输出是否符合预期
     * 
     * @param fail_idx  失效门的下标, 默认为0
     * @param fail_type 失效类型, 默认为0
     */
    bool check(const int& fail_idx=0, const int& fail_type=0) {
        for (int behavior_idx = 0; behavior_idx < num_behaviors; behavior_idx++) {
            reset_vst();
            for (int o_idx = 0; o_idx < num_outputs; o_idx++) {
                if (get_output(behavior_idx, output_idx[o_idx], fail_idx, fail_type) != expected_output[behavior_idx][o_idx])
                    return false;
            }
        }
        return true;
    }

    void solve() {
        if (check()) { printf("No faults detected\n"); return; }
        int fault_cnt = 0, fail_idx = 0, fail_type = 0;
        for (int f_idx = 1; f_idx <= num_gates; f_idx++) {
            for (int f_type = 0; f_type < 3; f_type++) {
                if (check(f_idx, f_type)) {
                    fault_cnt++;
                    if (fault_cnt > 1) {
                        printf("Unable to totally classify the failure\n");
                        return;
                    }
                    fail_idx = f_idx; fail_type = f_type;
                }
            }
        }
        printf("Gate %d is failing; output %s\n", fail_idx, fail_info_str[fail_type]);
    }
};
const char* Solver::fail_info_str[] = {"inverted", "stuck at 0", "stuck at 1"};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("G.in", "r", stdin);
    #endif

    Solver solver;
    int num_inputs, num_gates, num_outputs, num_behaviors;
    int input_type, input_idx;
    int case_cnt = 0;
    while (solver.input()) {
        printf("Case %d: ", ++case_cnt);
        solver.solve();
    }
    return 0;
}