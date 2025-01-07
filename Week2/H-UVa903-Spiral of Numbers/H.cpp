#include <iostream>
#include <cstdint>
using namespace std;

pair<int64_t, int64_t> get_pos(const int64_t &x) {
    int64_t left = 0, right = (1 << 15) + 1;
    while (left < right) {
        int64_t mid = (left + right) / 2;
        if ((2*mid+1)*(2*mid+1) < x) left = mid + 1;
        else right = mid;
    }
    int64_t i = x - (2*left-1)*(2*left-1);
    if (i <= 2*left) return {left, left-i};
    else if (i <= 4*left) return {3*left-i, -left};
    else if (i <= 6*left) return {-left, i-5*left};
    else return {i-7*left, left};
}

int64_t get_num(const int64_t &x, const int64_t &y) {
    int64_t num_circ = max(abs(x), abs(y));
    if (x == num_circ && y < num_circ) return (2*num_circ-1)*(2*num_circ-1) + num_circ - y;
    else if (y == -num_circ) return (2*num_circ-1)*(2*num_circ-1) + 3*num_circ - x;
    else if (x == -num_circ) return (2*num_circ-1)*(2*num_circ-1) + 5*num_circ + y;
    else return (2*num_circ-1)*(2*num_circ-1) + 7*num_circ + x;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("H.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int64_t n;
    while(cin >> n) {
        auto pos = get_pos(n);
        auto x = pos.first, y = pos.second;
        cout << get_num(x-1, y+1) << ";" << get_num(x, y+1) << ";" << get_num(x+1, y+1) << ";" << endl;
        cout << get_num(x-1, y) << ";" << n << ";" << get_num(x+1, y) << ";" << endl;
        cout << get_num(x-1, y-1) << ";" << get_num(x, y-1) << ";" << get_num(x+1, y-1) << ";" << endl;
    }
    return 0;
}