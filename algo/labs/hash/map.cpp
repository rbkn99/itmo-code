#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

class HashTable {
public:
    explicit HashTable(long long values_range) {
        size = get_size(values_range);
        table.resize(size);
    }

    void put(string &k, string &v) {
        int i = hash(k);
        if (!get(k).empty()) {
            for (auto j = 0; j < table[i].size(); j++) {
                if (table[i][j].first == k) {
                    table[i][j].second = v;
                    return;
                }
            }
        }
        table[i].push_back(make_pair(k, v));
    }

    string get(string &key) {
        int j = hash(key);
        for (auto &el: table[j]) {
            if (el.first == key)
                return el.second;
        }
        return "";
    }

    void remove(string &key) {
        if (get(key).empty())
            return;
        int i = hash(key);
        for (auto it = table[i].begin(); it != table[i].end(); ++it) {
            if ((*it).first == key) {
                table[i].erase(it);
                return;
            }
        }
    }

private:
    vector<vector<pair<string, string> > > table;
    size_t size;

    size_t get_size(long long range) {
        size_t prime_numbers[] = {1487, 17239, 93133, 99907};
        if (range < (1 << 10))
            return prime_numbers[0];
        if (range < (1 << 20))
            return prime_numbers[1];
        if (range < (1 << 30))
            return prime_numbers[2];
        return prime_numbers[3];
    }

    int hash(string &s) {
        int prime_number = 31, q = 1;
        int sum = 0;
        for (auto c: s) {
            sum += q * c;
            q *= prime_number;
        }
        return int(abs(sum) % size);
    }
};

int main() {
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    string com, k, v;
    HashTable hashTable(2000000000);
    while (true) {
        com = "";
        cin >> com >> k;
        if (com.empty())
            break;
        if (com == "put") {
            cin >> v;
            hashTable.put(k, v);
        }
        else if (com == "delete") {
            hashTable.remove(k);
        }
        else {
            string result = hashTable.get(k);
            if (result.empty())
                cout << "none\n";
            else
                cout << result << endl;
        }
    }
    return 0;
}