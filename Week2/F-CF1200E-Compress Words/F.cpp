#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#define MAX_STR_LENGTH 1000005
using namespace std;

int pow1[MAX_STR_LENGTH] = {0}, pow2[MAX_STR_LENGTH] = {0};

class StringWithHash {
  public:
    const int base1 = 71;
    const int mod1 = 5021;
    const int base2 = 122;
    const int mod2 = 5777;
    string str = "";
    vector<int> prefix_hash1, prefix_hash2;
    int cur_hash1 = 0, cur_hash2 = 0;
    int cur_pow1 = 1, cur_pow2 = 1;

    inline void add_char(const char &ch) {
        str += ch;
        int &&len = str.length();
        pow1[len-1] = cur_pow1; cur_pow1 = cur_pow1 * base1 % mod1;
        pow2[len-1] = cur_pow2; cur_pow2 = cur_pow2 * base2 % mod2;
        cur_hash1 = (cur_hash1 * base1 + ch) % mod1;
        prefix_hash1.push_back(cur_hash1);
        cur_hash2 = (cur_hash2 * base2 + ch) % mod2;
        prefix_hash2.push_back(cur_hash2);
    }

    void add_string(const string &ss) {
        for (auto& ch : ss) add_char(ch);
    }

    // 获取 [l, r] 的hash值
    tuple<int, int> get_hash(const int &l, const int &r) {
        if (l == 0) return make_tuple(prefix_hash1[r], prefix_hash2[r]);
        int hash1 = (prefix_hash1[r] - prefix_hash1[l-1] * pow1[r-l+1]) % mod1;
        hash1 = (hash1 + mod1) % mod1;
        int hash2 = (prefix_hash2[r] - prefix_hash2[l-1] * pow2[r-l+1]) % mod2;
        hash2 = (hash2 + mod2) % mod2;
        return make_tuple(hash1, hash2);
    }
};
StringWithHash strhash;

int main() {
    #ifndef ONLINE_JUDGE
        freopen("F.in", "r", stdin);
    #endif
    ios::sync_with_stdio(false);

    int num_words, len;
    string ss;
    cin >> num_words;
    for (int word_cnt = 0; word_cnt < num_words; word_cnt++) {
        cin >> ss;
        StringWithHash strhash_tmp;
        strhash_tmp.add_string(ss);
        // 找最大匹配长度len
        for (len = min(ss.length(), strhash.str.length()); len > 0; len--) {
            // strhash: [str.length()-len, str.length()-1]
            // ss:      [0, len-1]
            if (strhash.get_hash(strhash.str.length()-len, strhash.str.length()-1) == strhash_tmp.get_hash(0, len-1)) break;
        }
        strhash.add_string(ss.substr(len));
    }
    cout << strhash.str << endl;
    return 0;
}