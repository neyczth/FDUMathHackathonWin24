#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("L.in", "r", stdin);
    #endif
    int num_cases;
    int x;
    scanf("%d", &num_cases);
    while(num_cases--) {
        priority_queue<int> pq1;
        priority_queue<int, vector<int>, greater<int>> pq2;
        while (scanf("%d", &x) != EOF) {
            if (!x) break;
            if (x > 0) {
                if (pq1.empty()) pq1.push(x);
                else if (x <= pq1.top()) {
                    pq1.push(x);
                    if (pq1.size() > pq2.size() + 1) {
                        pq2.push(pq1.top());
                        pq1.pop();
                    }
                }
                else {
                    pq2.push(x);
                    if (pq2.size() > pq1.size()) {
                        pq1.push(pq2.top());
                        pq2.pop();
                    }
                }
            }
            else {
                printf("%d\n", pq1.top());
                pq1.pop();
                if (pq1.size() < pq2.size()) {
                    pq1.push(pq2.top());
                    pq2.pop();
                }
            }
        }
    }
    return 0;
}