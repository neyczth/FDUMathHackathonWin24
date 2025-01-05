#include <iostream>
#include <string>
using namespace std;

int get_split_number(const string &str_num_to_cut, int cut_info) {
    int cur = 0, output = 0;
    for (int i = 0; i < str_num_to_cut.size(); i++) {
        cur = cur*10 + str_num_to_cut[i] - '0';
        if (cut_info & 1) output += cur, cur = 0;
        cut_info >>= 1;
    }
    output += cur;
    return output;
}

string get_split_string(const string &str_num_to_cut, int cut_info) {
    string output;
    for (int i = 0; i < str_num_to_cut.size(); i++) {
        output += str_num_to_cut[i];
        if (cut_info & 1) output += ' ';
        cut_info >>= 1;
    }
    return output;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("A.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int num_to_get, best_ans = -1, best_ans_cnt = 0, best_cut_info = 0;
    string str_num_to_cut;

    while (cin >> num_to_get >> str_num_to_cut) {
        if (!num_to_get) break;

        best_ans = -1; best_ans_cnt = 0;
        if (num_to_get == stoi(str_num_to_cut)) {
            cout << num_to_get << ' ' << num_to_get << endl;
            continue;
        }

        for (int cut_info = 0; cut_info < (1 << (str_num_to_cut.size()-1)); cut_info++) {
            int &&split_number = get_split_number(str_num_to_cut, cut_info);
            if (split_number <= num_to_get) {
                if (split_number == best_ans) best_ans_cnt++;
                else if (split_number > best_ans) {
                    best_ans = split_number;
                    best_ans_cnt = 1;
                    best_cut_info = cut_info;
                }
            }
        }

        if (best_ans == -1) cout << "error" << endl;
        else if (best_ans_cnt > 1) cout << "rejected" << endl;
        else cout << best_ans << ' ' << get_split_string(str_num_to_cut, best_cut_info) << endl;
    }

    return 0;
}