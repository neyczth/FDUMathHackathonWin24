#include <iostream>
#include <string>
using namespace std;

string preorder, inorder;

void find_postorder(const int &pre_l, const int &pre_r,
                    const int & in_l, const int & in_r) {
    if (pre_r <= pre_l) return;
    char root_name = preorder[pre_l];
    int root_idx = in_l;
    while (inorder[root_idx] != root_name) root_idx++;
    find_postorder(pre_l+1, pre_l+1+root_idx-in_l, in_l, root_idx);
    find_postorder(pre_r-(in_r-root_idx-1), pre_r, root_idx+1, in_r);
    cout << root_name;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("H.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    while (cin >> preorder >> inorder) {
        int length = preorder.size();
        find_postorder(0, length, 0, length);
        cout << endl;
    }

    return 0;
}