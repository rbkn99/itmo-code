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
        last = "";
    }

    void put(string &k, string &v) {
        int i = hash(k);
        if (!get(k).empty()) {
            for (auto j = 0; j < table[i].size(); j++) {
                if (table[i][j].key == k) {
                    table[i][j].value = v;
                }
            }
        }
        else {
            table[i].emplace_back(Key(k, v));
            table[i][table[i].size() - 1].prev = last;
            if (!last.empty()) {
                upd_key(last, k);
            }
            last = k;
        }
    }

    string get(string &key) {
        int j = hash(key);
        for (auto &el: table[j]) {
            if (el.key == key)
                return el.value;
        }
        return "";
    }

    void remove(string &key) {
        if (get(key).empty())
            return;
        int i = hash(key);

        for (auto it = table[i].begin(); it != table[i].end(); ++it) {
            if (it->key == key) {
                if (key == last) {
                    last = it->prev;
                }
                if (!(it->prev.empty()))
                    upd_key(it->prev, it->next);
                if (!(it->next.empty()))
                    upd_key(it->next, it->prev, true);
                table[i].erase(it);
                return;
            }
        }
    }

    string prev(string& key) {
        int i = hash(key);
        for (auto el: table[i]) {
            if (el.key == key) {
                return get(el.prev);
            }
        }
        return "";
    }

    string next(string& key) {
        int i = hash(key);
        for (auto el: table[i]) {
            if (el.key == key) {
                return get(el.next);
            }
        }
        return "";
    }
private:
    struct Key {
        string key;
        string value;
        string prev;
        string next;
        Key() : key(""), value(""), prev(""), next("") {}
        Key(const string& _key, const string& _value) {
            key = _key;
            value = _value;
            prev = "";
            next = "";
        }
    };

    string last;
    vector<vector<Key> > table;
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

    void upd_key(string& key, string& new_str, bool is_prev=false) {
        int i = hash(key);
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j].key == key) {
                if (is_prev) {
                    table[i][j].prev = new_str;
                }
                else {
                    table[i][j].next = new_str;
                }
                return;
            }
        }
    }
};

int main() {
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);
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
        else if (com == "get") {
            string result = hashTable.get(k);
            if (result.empty())
                cout << "none\n";
            else
                cout << result << endl;
        }
        else if (com == "prev") {
            string result = hashTable.prev(k);
            if (result.empty())
                cout << "none\n";
            else
                cout << result << endl;
        }
        else if (com == "next") {
            string result = hashTable.next(k);
            if (result.empty())
                cout << "none\n";
            else
                cout << result << endl;
        }
    }
    return 0;
}
