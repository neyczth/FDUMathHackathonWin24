#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

class Matrix {
  public:
    int size[2] = {0};

    void set_size(const int &num_row, const int &num_col) {
        size[0] = num_row;
        size[1] = num_col;
    }
};
vector<Matrix> matrix_list(26);

uint64_t ans = 0;
bool err_flag = 0;
class MatrixMultiplyHandler {
  public:
    bool has_matrix = 0;
    Matrix cur_matrix = Matrix();

    void add_matrix(const Matrix& mat) {
        const int& num_row = mat.size[0];
        const int& num_col = mat.size[1];
        if (!has_matrix) {
            cur_matrix.set_size(num_row, num_col);
            has_matrix = 1;
        }
        else {
            if (num_row != cur_matrix.size[1]) { err_flag = 1; return; }
            ans += cur_matrix.size[0] * cur_matrix.size[1] * num_col;
            cur_matrix.size[1] = num_col;
        }
    }
};
stack<MatrixMultiplyHandler> st;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("F.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int num_matrix, num_row, num_col;
    char matrix_name;
    cin >> num_matrix;
    for (int i = 0; i < num_matrix; i++) {
        cin >> matrix_name >> num_row >> num_col;
        matrix_list[matrix_name-'A'].set_size(num_row, num_col);
    }

    string ss;
    getline(cin, ss);
    Matrix tmp_matrix;
    while (getline(cin, ss)) {
        // Init
        while(!st.empty()) st.pop();
        err_flag = 0;
        ans = 0;

        st.push(MatrixMultiplyHandler());
        for (int i = 0; i < ss.size(); i++) {
            if (err_flag) break;
            char &ch = ss[i];

            if (ch == '(') st.push(MatrixMultiplyHandler());
            else if (ch == ')') {
                auto &cur_handler = st.top();
                tmp_matrix = cur_handler.cur_matrix;
                st.pop();
                if (!st.empty()) {
                    auto &cur_handler = st.top();
                    cur_handler.add_matrix(tmp_matrix);
                }
            }
            else {
                auto &cur_handler = st.top();
                cur_handler.add_matrix(matrix_list[ch - 'A']);
            }
        }

        if (err_flag) cout << "error" << endl;
        else cout << ans << endl;
    }

    return 0;
}