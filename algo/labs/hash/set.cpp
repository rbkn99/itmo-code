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

    void insert(int value) {
        if (exists(value))
            return;
        table[hash(value)].push_back(value);
    }

    bool exists(int value) {
        int j = hash(value);
        for (auto el: table[j]) {
            if (el == value)
                return true;
        }
        return false;
    }

    void remove(int value) {
        if (!exists(value))
            return;
        int i = hash(value);
        table[i].erase(std::remove(table[i].begin(), table[i].end(), value), table[i].end());
    }

private:
    vector<vector<int> > table;
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

    int hash(int key) {
        return int(abs(key) % size);
    }
};

int main() {
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    char com[8];
    int value;
    HashTable hashTable(2000000000);
    while (scanf("%s%d", com, &value) != EOF) {
        if (strcmp(com, "insert") == 0) {
            hashTable.insert(value);
            continue;
        }
        if (strcmp(com, "exists") == 0) {
            bool result = hashTable.exists(value);
            if (result)
                printf("true\n");
            else
                printf("false\n");
            continue;
        }
        if (strcmp(com, "delete") == 0) {
            hashTable.remove(value);
        }
    }
    return 0;
}