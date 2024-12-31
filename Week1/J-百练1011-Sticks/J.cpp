#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_STICK 70
using namespace std;

vector<int> sticks(MAX_STICK);
vector<bool> vst(MAX_STICK, 0);
int sum_length = 0, trial_length = 0;
int num_sticks;

bool backtracking(const int &num_corr_stick, const int &corr_length) {
    if (num_corr_stick >= sum_length / trial_length) return true;

    bool is_ok = 0;
    for (int i = 0; i < num_sticks; i++) {
        int &&rest_length = trial_length - corr_length;
        if (!vst[i] && sticks[i] <= rest_length) {
            vst[i] = true;
            if (rest_length == sticks[i]) is_ok |= backtracking(num_corr_stick+1, 0);
            else is_ok |= backtracking(num_corr_stick, corr_length + sticks[i]);
            if (is_ok) return true;
            vst[i] = false;
            if (corr_length == 0 || rest_length == sticks[i]) break;
        }
    }

    return false;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("J.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int max_length = 0;
    while (cin >> num_sticks) {
        if (!num_sticks) break;

        sum_length = 0; max_length = 0;
        vst.assign(vst.size(), 0);
        for (int i = 0; i < num_sticks; i++) {
            cin >> sticks[i];
            sum_length += sticks[i];
            max_length = max(max_length, sticks[i]);
        }
        sort(sticks.begin(), sticks.begin() + num_sticks, greater<int>());

        for (trial_length = max_length; trial_length <= sum_length; trial_length++) {
            if (sum_length % trial_length != 0) continue;
            if (backtracking(0, 0)) {
                cout << trial_length << endl;
                break;
            }
        }
    }

    return 0;
}