#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#define MAXN 70
using namespace std;

class QuadTree {
  public:
    int dim = 0;
    bool num[MAXN][MAXN] = {0};
    vector<int> quadtree_rep;

    void reset() {
        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < MAXN; j++)
                num[i][j] = 0;
    }

    void set_dim(const int &_d) { dim = _d; }

    void set_one(int x) {
        int u = 0, d = dim, l = 0, r = dim;
        while (x) {
            switch (x%5) {
                case 1: // NW
                    r = (l + r) / 2; d = (u + d) / 2; break;
                case 2: // NE
                    l = (l + r) / 2; d = (u + d) / 2; break;
                case 3: // SW
                    r = (l + r) / 2; u = (u + d) / 2; break;
                case 4: // SE
                    l = (l + r) / 2; u = (u + d) / 2; break;
            }
            x /= 5;
        }
        for (int i = u; i < d; i++)
            for (int j = l; j < r; j++)
                num[i][j] = 1;
    }

    int check(const int &u, const int &d, const int &l, const int &r) {
        int ans = 0;
        for (int i = u; i < d; i++)
            for (int j = l; j < r; j++)
                ans += num[i][j];
        if (ans == 0) return 0;
        if (ans == (d-u) * (r-l)) return 1;
        return -1;
    }

    void build_quadtree(const int &cur_x, const int &layer, const int &u, const int &d, const int &l, const int &r) {
        if (d <= u || r <= l) return;

        int check_res = check(u, d, l, r);
        if (check_res == 1) {
            quadtree_rep.push_back(cur_x);
        }
        else if (check_res == -1) {
            int &&xmid = (u+d)/2, ymid = (l+r)/2;
            build_quadtree(cur_x+1*layer, layer*5, u, xmid, l, ymid);
            build_quadtree(cur_x+2*layer, layer*5, u, xmid, ymid, r);
            build_quadtree(cur_x+3*layer, layer*5, xmid, d, l, ymid);
            build_quadtree(cur_x+4*layer, layer*5, xmid, d, ymid, r);
        }
    }

    void get_quadtree_representation() {
        quadtree_rep.clear();
        build_quadtree(0, 1, 0, dim, 0, dim);
        sort(quadtree_rep.begin(), quadtree_rep.end());
    }

    void print() {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) cout << (num[i][j] ? '*' : '.');
            cout << endl;
        }
    }
};
QuadTree quadtree;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("I.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int dim;
    int x;
    int test_cnt = 0;
    string ss;
    while (1) {
        test_cnt++;
        cin >> dim;
        if (dim == 0) break;

        quadtree.reset();
        getline(cin, ss);
        if (test_cnt > 1) cout << endl;
        cout << "Image " << test_cnt << endl;
        if (dim > 0) {
            quadtree.set_dim(dim);
            for (int i = 0; i < dim; i++) {
                getline(cin, ss);
                for (int j = 0; j < dim; j++) quadtree.num[i][j] = ss[j] - '0';
            }
            quadtree.get_quadtree_representation();
            if (!quadtree.quadtree_rep.empty()) {
                cout << quadtree.quadtree_rep[0];
                for (int i = 1; i < quadtree.quadtree_rep.size(); i++) {
                    if (i % 12 == 0) cout << endl;
                    else cout << ' ';
                    cout << quadtree.quadtree_rep[i];
                }
                cout << endl;
            }
            cout << "Total number of black nodes = " << quadtree.quadtree_rep.size() << endl;
        }
        else {
            quadtree.set_dim(-dim);
            while (1) {
                cin >> x; if (x == -1) break;
                quadtree.set_one(x);
            }
            quadtree.print();
        }
    }
    return 0;
}