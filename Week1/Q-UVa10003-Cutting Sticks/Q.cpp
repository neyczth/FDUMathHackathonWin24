#include <iostream>
#include <algorithm>
#include <cstdint>
#define NUM_CUT 105
#define INF 0x7f7f7f7f7f7f7f7f
using namespace std;

uint64_t dp[NUM_CUT][NUM_CUT] = {0};
int pos[NUM_CUT] = {0};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("Q.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);
    int stick_length, num_cut;

    while (cin >> stick_length) {
        if (!stick_length) break;

        cin >> num_cut;
        pos[0] = 0; pos[num_cut+1] = stick_length;
        for (int i = 1; i <= num_cut; i++) cin >> pos[i];

        for (int i = 0; i <= num_cut-1; i++)
            for (int j = i+2; j <= num_cut+1; j++)
                dp[i][j] = INF;
        for (int i = 0; i <= num_cut; i++)
            dp[i][i+1] = 0;

        for (int len = 2; len <= num_cut+1; len++)
            for (int i = 0; i + len <= num_cut+1; i++) {
                for (int k = i+1; k < i+len; k++) {
                    dp[i][i+len] = min(dp[i][i+len], dp[i][k] + dp[k][i+len]);
                }
                dp[i][i+len] += pos[i+len] - pos[i];
            }

        cout << "The minimum cutting is " << dp[0][num_cut+1] << '.' << endl;
    }

    return 0;
}