#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;

class WeightedDisjointSet {
  public:
    vector<int> parent, rank;
    vector<int> weight;  // 与根的异或值

    // 初始化一个 num_nodes+1 个节点的带权并查集
    void init(const int &num_nodes) {
        parent.resize(num_nodes);
        rank.resize(num_nodes);
        weight.resize(num_nodes);
        for (int i = 0; i < num_nodes; i++) {
            parent[i] = i;
            rank[i] = 0;
            weight[i] = 0;
        }
    }

    int find(const int &idx) {
        if (parent[idx] == idx) return idx;
        int root = find(parent[idx]);
        weight[idx] ^= weight[parent[idx]];
        // 对 x->y->...->root这条链来说, 递归后链已经变成了x->y->root
        // weight[x] = x^y, weight[y] = y^root
        // 现在想要x->root, 那么
        // weight[x] = x^root = (x^y) ^ (y^root) = weight[x] ^ weight[y]
        return parent[idx] = root;
    }

    bool union_set(const int &x, const int &y, const int &xor_value) {
        int root_x = find(x), root_y = find(y);
        if (root_x == root_y) {
            // 检查是否与已知条件冲突
            return (weight[x] ^ weight[y]) == xor_value;
        }
        if (rank[root_x] < rank[root_y]) {
            parent[root_x] = root_y;
            weight[root_x] = weight[x] ^ weight[y] ^ xor_value;
        } else {
            parent[root_y] = root_x;
            weight[root_y] = weight[x] ^ weight[y] ^ xor_value;
            if (rank[root_x] == rank[root_y]) rank[root_x]++;
        }
        return true;
    }
};

class Solver {
  public:
    int num_nums = 0, num_queries = 0;
    WeightedDisjointSet wds;
    int case_cnt = 0;

    void solve() {
        string ss;
        char query_type;
        int case_cnt = 0;
        int num;
        int I_cnt = 0;
        bool end_flag = false;
        vector<int> input_nums;
        while (true) {
            cin >> num_nums >> num_queries;
            if (!num_nums && !num_queries) return;

            getline(cin, ss);  // 吞掉换行符
            I_cnt = 0; end_flag = false;
            wds.init(num_nums+1);  // 初始化一个num_nums+1个节点的并查集, 其中idx=num_nums是值为0的虚拟节点
            cout << "Case " << ++case_cnt << ":" << endl;
            for (int i = 0; i < num_queries; i++) {
                input_nums.clear();
                getline(cin, ss);
                if (end_flag) continue;  // 在已经出现冲突的情况下, 吞掉剩余的输入信息

                istringstream iss(ss);
                iss >> query_type;
                while (iss >> num) input_nums.push_back(num);
                if (query_type == 'I') {
                    I_cnt++;
                    int union_res;
                    if (input_nums.size() == 2)
                        union_res = wds.union_set(input_nums[0], num_nums, input_nums[1]);
                    else
                        union_res = wds.union_set(input_nums[0], input_nums[1], input_nums[2]);
                    if (!union_res) {
                        cout << "The first " << I_cnt << " facts are conflicting." << endl;
                        end_flag = true;
                    }
                }
                else {
                    map<int, int> root_cnt;
                    int tmp = 0;
                    for (int j = 1; j < input_nums.size(); j++) {
                        int root_j = wds.find(input_nums[j]);
                        if (root_cnt.find(root_j) != root_cnt.end()) root_cnt[root_j]++;
                        else root_cnt[root_j] = 1;
                        tmp ^= wds.weight[input_nums[j]];
                    }
                    bool dont_know = false;
                    int root_0 = wds.find(num_nums);
                    for (auto &p : root_cnt) {
                        if (p.first != root_0 && (p.second & 1)) {
                            dont_know = true;
                            break;
                        }
                    }
                    if (dont_know) cout << "I don't know." << endl;
                    else {
                        if (root_cnt.find(root_0) != root_cnt.end() && (root_cnt[root_0] & 1))
                            tmp ^= wds.weight[num_nums];
                        cout << tmp << endl;
                    }
                }
            }
            cout << endl;
        }
    }
};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("M.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    Solver solver;
    solver.solve();
    return 0;
}