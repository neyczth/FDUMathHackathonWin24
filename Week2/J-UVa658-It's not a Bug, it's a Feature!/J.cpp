#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <queue>
#include <cstring>
#define MAX_NUM_PATCHES 105
#define MAX_NUM_STATUS ((1 << 20) + 5)
using namespace std;

int num_bugs, num_patches;

class Patch {
  public:
    int time = 0;
    int use_present = 0, use_absent = 0;
    int introduce_list = 0, fix_list = 0;
};
vector<Patch> patches(MAX_NUM_PATCHES);
bool vst[MAX_NUM_STATUS];

struct Heapnode {
    int status = 0;
    int time = 0;

    Heapnode(const int &_status, const int _time) : status(_status), time(_time) {}

    bool operator< (const Heapnode &rhs) const {
        return time > rhs.time;
    }
};

int main() {
    #ifndef ONLINE_JUDGE
        freopen("J.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    string ss;
    int case_cnt = 0;
    while (cin >> num_bugs >> num_patches) {
        if (!num_bugs && !num_patches) break;
        
        cout << "Product " << ++case_cnt << endl;
        for (int i = 0; i < num_patches; i++) {
            cin >> patches[i].time;
            cin >> ss;
            patches[i].use_present = patches[i].use_absent = 0;
            for (auto &ch : ss) {
                patches[i].use_present = (patches[i].use_present << 1) | (ch == '+');
                patches[i].use_absent = (patches[i].use_absent << 1) | (ch == '-');
            }
            cin >> ss;
            patches[i].introduce_list = patches[i].fix_list = 0;
            for (auto &ch : ss) {
                patches[i].introduce_list = (patches[i].introduce_list << 1) | (ch == '+');
                patches[i].fix_list = (patches[i].fix_list << 1) | (ch == '-');
            }
        }
        int start_status = (1 << num_bugs) - 1, end_status = 0;

        // 隐式图上的Dijkstra
        memset(vst, 0, sizeof vst);
        priority_queue<Heapnode> q;
        q.push(Heapnode(start_status, 0));
        while (!q.empty()) {
            Heapnode now = q.top(); q.pop();
            if (vst[now.status]) continue;
            vst[now.status] = true;
            if (now.status == end_status) {
                cout << "Fastest sequence takes " << now.time << " seconds." << endl;
                break;
            }
            for (int i = 0; i < num_patches; i++) {
                int next_status = now.status;
                if ((now.status & patches[i].use_present) == patches[i].use_present &&
                    (~now.status & patches[i].use_absent) == patches[i].use_absent) {
                    next_status |= patches[i].introduce_list;
                    next_status &= ~patches[i].fix_list;
                    if (!vst[next_status]) {
                        q.push(Heapnode(next_status, now.time + patches[i].time));
                    }
                }
            }
        }
        if (!vst[end_status]) {
            cout << "Bugs cannot be fixed." << endl;
        }
        cout << endl;
    }

    return 0;
}