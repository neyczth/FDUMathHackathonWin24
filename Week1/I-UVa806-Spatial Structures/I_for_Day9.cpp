#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#define MAXN 70
using namespace std;

// 四叉树类
class QuadTree {
  public:
    int dim = 0;                 // 图像维度
    bool num[MAXN][MAXN] = {0};  // 存储二维数组的布尔值
    vector<int> quadtree_rep;    // 存储四叉树的五进制码表示

    // 设置图像维度
    void set_dim(const int &_d) { dim = _d; }

    /**
     * @brief 检查指定区域内的元素情况
     * 
     * @param i_low  区域的行下界
     * @param i_high 区域的行上界
     * @param j_low  区域的列下界
     * @param j_high 区域的列上界
     * @return int 返回值为0表示区域内均为0; 返回值为1表示区域内均为1; 返回值为-1表示区域内元素既有0又有1
     */
    int check(const int &i_low, const int &i_high, const int &j_low, const int &j_high) {
        int cnt = 0;
        for (int i = i_low; i < i_high; i++)
            for (int j = j_low; j < j_high; j++)
                cnt += num[i][j];
        if (cnt == 0) return 0;
        if (cnt == (i_high-i_low)*(j_high-j_low)) return 1;
        return -1;
    }

    /**
     * @brief 递归获取四叉树的五进制码表示
     * 
     * @param cur_x 当前区域的五进制编码
     * @param layer 当前区域的层数 (5的幂)
     * @param i_low,i_high 当前区域的行范围 [i_low, i_high)
     * @param j_low,j_high 当前区域的列范围 [j_low, j_high)
     */
    void build_quadtree(const int &cur_x, const int &layer, const int &i_low, const int &i_high, const int &j_low, const int &j_high) {
        if (i_high <= i_low || j_high <= j_low) return;

        int check_res = check(i_low, i_high, j_low, j_high);
        if (check_res == 1) {
            quadtree_rep.push_back(cur_x);
        }
        else if (check_res == -1) {
            int &&i_mid = (i_low+i_high)/2, j_mid = (j_low+j_high)/2;
            build_quadtree(cur_x+1*layer, layer*5, i_low,  i_mid, j_low,  j_mid);    // NW
            build_quadtree(cur_x+2*layer, layer*5, i_low,  i_mid, j_mid, j_high);   // NE
            build_quadtree(cur_x+3*layer, layer*5, i_mid, i_high, j_low,  j_mid);   // SW
            build_quadtree(cur_x+4*layer, layer*5, i_mid, i_high, j_mid, j_high);  // SE
        }
    }

    /**
     * @brief 获取四叉树的五进制码表示
     */
    void get_quadtree_representation() {
        quadtree_rep.clear();
        build_quadtree(0, 1, 0, dim, 0, dim);
        sort(quadtree_rep.begin(), quadtree_rep.end());
    }

    /**
     * @brief 将指定位置的元素设置为1
     * 
     * @param x 区域的五进制编码
     */
    void set_one(int x) {
        int i_low = 0, i_high = dim, j_low = 0, j_high = dim;
        while (x) {
            int i_mid = (i_low + i_high) / 2, j_mid = (j_low + j_high) / 2;
            switch (x % 5) {
                case 1: i_high = i_mid; j_high = j_mid; break;  // NW
                case 2: i_high = i_mid; j_low  = j_mid; break;  // NE
                case 3: i_low  = i_mid; j_high = j_mid; break;  // SW
                case 4: i_low  = i_mid; j_low  = j_mid; break;  // SE
            }
            x /= 5;
        }
        for (int i = i_low; i < i_high; i++)
            for (int j = j_low; j < j_high; j++)
                num[i][j] = 1;
    }

    /**
     * @brief 打印二维数组的内容
     */
    void print() {
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) putchar(num[i][j] ? '*' : '.');
            putchar('\n');
        }
    }
};
QuadTree quadtree;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("I.in", "r", stdin);
    #endif

    int dim, x;
    int test_cnt = 0;
    char ss[MAXN];
    while (true) {
        scanf("%d", &dim);
        if (dim == 0) break;

        fgets(ss, sizeof(ss), stdin);  // 吃掉行末换行符
        if (test_cnt++) putchar('\n');
        printf("Image %d\n", test_cnt);

        if (dim > 0) {  // 0-1阵转四叉树
            quadtree.set_dim(dim);
            for (int i = 0; i < dim; i++) {
                fgets(ss, sizeof(ss), stdin);
                for (int j = 0; j < dim; j++) quadtree.num[i][j] = ss[j] - '0';
            }
            quadtree.get_quadtree_representation();
            if (!quadtree.quadtree_rep.empty()) {
                for (int i = 0; i < quadtree.quadtree_rep.size(); i++) {
                    if (i > 0 && i % 12 == 0) putchar('\n');
                    else if (i > 0) putchar(' ');
                    printf("%d", quadtree.quadtree_rep[i]);
                }
                putchar('\n');
            }
            printf("Total number of black nodes = %d\n", quadtree.quadtree_rep.size());
        }

        else {  // 五进制码转0-1阵
            quadtree.set_dim(-dim);
            while (true) {
                scanf("%d", &x); if (x == -1) break;
                quadtree.set_one(x);
            }
            quadtree.print();
        }
    }
    return 0;
}