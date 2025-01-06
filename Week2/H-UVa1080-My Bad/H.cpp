#include <cstdio>
#include <cstring>
#define MAX_NUM_INPUTS    10
#define MAX_NUM_GATES     25
#define MAX_NUM_OUTPUTS   25
#define MAX_NUM_BEHAVIOR 260
using namespace std;

int num_inputs, num_gates, num_outputs, num_behaviors;
char gate_type, input_type;
int input_idx;
bool is_from_input[MAX_NUM_GATES][2] = {0};
int from_idx[MAX_NUM_GATES][2] = {0};
char gate_type_list[MAX_NUM_GATES];
int output_idx[MAX_NUM_OUTPUTS] = {0};
bool behavior_input[MAX_NUM_BEHAVIOR][MAX_NUM_INPUTS] = {0};
bool expected_output[MAX_NUM_BEHAVIOR][MAX_NUM_OUTPUTS] = {0};
bool vst[MAX_NUM_GATES] = {0};
bool output[MAX_NUM_GATES] = {0};
char fail_info_str[][20] = {"output inverted", "output stuck at 0", "output stuck at 1"};
int case_cnt = 0;

bool get_output(const int& behavior_idx, const int &gate_idx,
                const int& fail_idx=0, const int& fail_type=0) {
    // fail_type: 0 - inverted | 1 - stuck at 0 | 2 - stuck at 1
    if (vst[gate_idx]) return output[gate_idx];

    vst[gate_idx] = 1;
    if (fail_idx == gate_idx) {
        switch (fail_type) {
            case 1: output[gate_idx] = 0; return 0; break;
            case 2: output[gate_idx] = 1; return 1; break;
        }
    }

    bool input1 = 0, input2 = 0;
    if (is_from_input[gate_idx][0]) input1 = behavior_input[behavior_idx][from_idx[gate_idx][0]];
    else input1 = get_output(behavior_idx, from_idx[gate_idx][0], fail_idx, fail_type);
    if (gate_type_list[gate_idx] != 'n') {
        if (is_from_input[gate_idx][1]) input2 = behavior_input[behavior_idx][from_idx[gate_idx][1]];
        else input2 = get_output(behavior_idx, from_idx[gate_idx][1], fail_idx, fail_type);
    }
    bool ans;
    switch (gate_type_list[gate_idx]) {
        case 'a': ans = input1 & input2; break;
        case 'o': ans = input1 | input2; break;
        case 'x': ans = input1 ^ input2; break;
        case 'n': ans = !input1;         break;
    }
    if (fail_idx == gate_idx && fail_type == 0) ans ^= 1;
    output[gate_idx] = ans;
    return ans;
}

bool check(const int& fail_idx=0, const int& fail_type=0) {
    for (int behavior_idx = 0; behavior_idx < num_behaviors; behavior_idx++) {
        memset(vst, 0, sizeof vst);
        for (int o_idx = 0; o_idx < num_outputs; o_idx++) {
            if (get_output(behavior_idx, output_idx[o_idx], fail_idx, fail_type) != expected_output[behavior_idx][o_idx])
                return false;
        }
    }
    return true;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("H.in", "r", stdin);
    #endif

    while (scanf("%d %d %d", &num_inputs, &num_gates, &num_outputs) != EOF) {
        // Input
        if (!num_inputs && !num_gates && !num_outputs) break;
        for (int i = 1; i <= num_gates; i++) {
            scanf(" %c", &gate_type_list[i]);
            scanf(" %c%d", &input_type, &input_idx);
            is_from_input[i][0] = (input_type == 'i');
            from_idx[i][0] = input_idx;
            if (gate_type_list[i] != 'n') {
                scanf(" %c%d", &input_type, &input_idx);
                is_from_input[i][1] = (input_type == 'i');
                from_idx[i][1] = input_idx;
            }
        }
        for (int i = 0; i < num_outputs; i++) {
            scanf("%d", &output_idx[i]);
        }
        scanf("%d", &num_behaviors);
        for (int i = 0; i < num_behaviors; i++) {
            for (int j = 1; j <= num_inputs; j++) scanf("%d", &behavior_input[i][j]);
            for (int j = 0; j < num_outputs; j++) scanf("%d", &expected_output[i][j]);
        }

        // Check whether there is no faults
        printf("Case %d: ", ++case_cnt);
        if (check()) printf("No faults detected\n");
        else {
            int fault_cnt = 0, fail_idx = 0, fail_type = 0;
            for (int f_idx = 1; f_idx <= num_gates; f_idx++) {
                for (int f_type = 0; f_type < 3; f_type++) {
                    if (check(f_idx, f_type)) {
                        fault_cnt++;
                        if (fault_cnt > 1) break;
                        fail_idx = f_idx; fail_type = f_type;
                    }
                }
                if (fault_cnt > 1) break;
            }
            if (fault_cnt != 1) printf("Unable to totally classify the failure\n");
            else printf("Gate %d is failing; %s\n", fail_idx, fail_info_str[fail_type]);
        }
    }
    return 0;
}