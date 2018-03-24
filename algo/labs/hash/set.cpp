#include <iostream>
using namespace std;

class HashTable {
public:
    HashTable() {
        table.resize(DEFAULT_TABLE_SIZE);
    }

    HashTable()

private:
    vector<int> table;
    size_t hash_table_size;
    const size_t DEFAULT_TABLE_SIZE = 9300005;  // it's just 2^23.1488, there is no any magic sense
};

int main() {
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);


    return 0;
}