#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    #ifndef ONLINE_JUDGE
        freopen("E.in", "r", stdin);
    #endif

    string ss;
    vector<int> nums;
    int x;
    while (getline(cin, ss)) {
        cout << ss << endl;
        nums.clear();
        nums.push_back(0);  // 塞一个占位置

        istringstream iss(ss);
        while (iss >> x) nums.push_back(x);

        reverse(nums.begin() + 1, nums.end());
        for (int i = 1; i < nums.size()-1; i++) {
            // 当前要把nums[i]该有的数放回去, 要扫描的是[i, num.size()-1]
            int max_num = nums[i], max_idx = i;
            for (int j = i+1; j < nums.size(); j++) {
                if (nums[j] > max_num) {
                    max_idx = j;
                    max_num = nums[j];
                }
            }

            if (max_idx == i) continue;
            if (max_idx < nums.size()-1) {
                cout << max_idx << ' ';
                reverse(nums.begin() + max_idx, nums.end());
            }
            cout << i << ' ';
            reverse(nums.begin() + i, nums.end());
        }
        cout << 0 << endl;
    }

    return 0;
}