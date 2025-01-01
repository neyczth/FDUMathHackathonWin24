#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#define MAX_BOOK 505
#define MAX_SCRIBER 505
using namespace std;

vector<uint64_t> books(MAX_BOOK);
vector<string> scriber_work_list(MAX_SCRIBER);
int num_part = 0, num_book = 0;

bool is_ok(const uint64_t &part_length) {
    int used_part = 0, res_length = part_length;
    for (int i = 0; i < num_book; i++) {
        if (res_length >= books[i]) res_length -= books[i];
        else used_part++, res_length = part_length - books[i];
        if (used_part >= num_part) return false;
    }
    return true;
}

void print_part(const uint64_t &part_length) {
    // 从最后一个安排工作, 尽量多塞. 如果恰好剩每人一本书则不再塞.
    scriber_work_list.assign(num_part, "");
    int rest_cnt = num_book;
    int cur_part = num_part - 1, res_v = part_length;
    for (int i = num_book-1; i >= 0; i--) {
        if (res_v < books[i] || i < cur_part)
            { cur_part--; res_v = part_length - books[i]; }
        else { res_v -= books[i]; }
        scriber_work_list[cur_part] = to_string(books[i]) + " " + scriber_work_list[cur_part];
    }

    for (int i = 0; i < num_part; i++) {
        if (i) cout << " / ";
        cout << scriber_work_list[i].substr(0, scriber_work_list[i].size()-1);
    }
    cout << endl;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("N.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int tot_test;
    uint64_t tot_length = 0, max_length = 0;
    cin >> tot_test;
    while (tot_test--) {
        tot_length = 0;
        max_length = 0;
        cin >> num_book >> num_part;
        for (int i = 0; i < num_book; i++) {
            cin >> books[i];
            tot_length += books[i];
            max_length = max(max_length, books[i]);
        }
        uint64_t left = max_length, right = tot_length;
        while (right > left) {
            uint64_t &&mid = (left + right) / 2;
            if (is_ok(mid)) right = mid;
            else left = mid + 1;
        }
        print_part(left);
    }

    return 0;
}