#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_NUM 4005
using namespace std;

vector<int> a(MAX_NUM), b(MAX_NUM), c(MAX_NUM), d(MAX_NUM);

class Sum {
  public:
    int data = 0, cnt = 0;

    Sum(const int &_d=0, const int &_c=0): data(_d), cnt(_c) {}
};
constexpr int NUM_SUM = MAX_NUM*MAX_NUM;
vector<int> sum1_origin(NUM_SUM), sum2_origin(NUM_SUM);
vector<Sum> sum1_withcnt(NUM_SUM), sum2_withcnt(NUM_SUM);

int main() {
    #ifndef ONLINE_JUDGE
        freopen("N.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int tot_test, num_cnt;
    cin >> tot_test;
    for (int test_cnt = 0; test_cnt < tot_test; test_cnt++) {
        sum1_origin.clear(); sum2_origin.clear();
        sum1_withcnt.clear(); sum2_withcnt.clear();
        cin >> num_cnt;
        for (int i = 0; i < num_cnt; i++) cin >> a[i] >> b[i] >> c[i] >> d[i];

        for (int i = 0; i < num_cnt; i++)
            for (int j = 0; j < num_cnt; j++)
                sum1_origin.push_back(a[i] + b[j]);
        sort(sum1_origin.begin(), sum1_origin.end());
        int last_sum = sum1_origin[0];
        sum1_withcnt.push_back(Sum(sum1_origin[0], 1));
        for (int i = 1; i < num_cnt * num_cnt; i++) {
            if (sum1_origin[i] == last_sum) sum1_withcnt.back().cnt++;
            else {
                last_sum = sum1_origin[i];
                sum1_withcnt.push_back(Sum(sum1_origin[i], 1));
            }
        }

        for (int i = 0; i < num_cnt; i++)
            for (int j = 0; j < num_cnt; j++)
                sum2_origin.push_back(c[i] + d[j]);
        sort(sum2_origin.begin(), sum2_origin.end(), greater<int>());
        last_sum = sum2_origin[0];
        sum2_withcnt.push_back(Sum(sum2_origin[0], 1));
        for (int i = 1; i < num_cnt * num_cnt; i++) {
            if (sum2_origin[i] == last_sum) sum2_withcnt.back().cnt++;
            else {
                last_sum = sum2_origin[i];
                sum2_withcnt.push_back(Sum(sum2_origin[i], 1));
            }
        }

        int idx1 = 0, idx2 = 0;
        int ans = 0;
        while (idx1 < sum1_withcnt.size() && idx2 < sum2_withcnt.size()) {
            int &&trial = sum1_withcnt[idx1].data + sum2_withcnt[idx2].data;
            if (trial < 0) idx1++;
            else if (trial > 0) idx2++;
            else {
                ans += sum1_withcnt[idx1].cnt * sum2_withcnt[idx2].cnt;
                idx1++; idx2++;
            }
        }

        if (test_cnt) cout << endl;
        cout << ans << endl;
    }

    return 0;
}