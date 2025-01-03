#include <iostream>
#include <vector>
#define MAX_COMPUTER 10005
using namespace std;

class Node {
  public:
    int first_max = 0, second_max = 0, ans = 0;
    bool vst1 = false, vst2 = false;

    void reset() {
        first_max = second_max = ans = 0;
        vst1 = vst2 = false;
    }

    void update_max(const int &len) {
        if (len > second_max) second_max = len;
        if (second_max > first_max) swap(first_max, second_max);
    }
};
vector<Node> computer_list(MAX_COMPUTER);
vector<vector<pair<int, int>>> link_to_list(MAX_COMPUTER);

void dfs1(const int &idx) {
    computer_list[idx].vst1 = true;
    for (auto& edge : link_to_list[idx]) {
        const int& child_idx = edge.first, weight = edge.second;
        if (computer_list[child_idx].vst1) continue;
        dfs1(child_idx);
        computer_list[idx].update_max(weight + computer_list[child_idx].first_max);
    }
}

void dfs2(const int &idx) {
    computer_list[idx].vst2 = true;
    for (auto& edge : link_to_list[idx]) {
        const int& child_idx = edge.first, weight = edge.second;
        if (computer_list[child_idx].vst2) continue;
        if (computer_list[idx].first_max == weight + computer_list[child_idx].first_max) {
            computer_list[child_idx].update_max(weight + computer_list[idx].second_max);
        }
        else
            computer_list[child_idx].update_max(weight + computer_list[idx].first_max);
        dfs2(child_idx);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("R.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int num_computer = 0;
    int link_to = 0, edge_weight = 0;
    while (cin >> num_computer) {
        for (auto &list : link_to_list) list.clear();
        for (int i = 2; i <= num_computer; i++) {
            cin >> link_to >> edge_weight;
            link_to_list[i].push_back(make_pair(link_to, edge_weight));
            link_to_list[link_to].push_back(make_pair(i, edge_weight));
        }

        for (int i = 1; i <= num_computer; i++) computer_list[i].reset();
        dfs1(1); dfs2(1);
        for (int i = 1; i <= num_computer; i++)
            cout << computer_list[i].first_max << endl;
    }

    return 0;
}