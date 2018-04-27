#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

class AA_Tree {
public:
    AA_Tree() {
        root = nullptr;
        size = 0;
    }

    ~AA_Tree() {
        //rec_delete(root);
        //size = 0;
    }

    void delete_all() {
        rec_delete(root);
        root = nullptr;
        size = 0;
    }

    size_t get_size() {
        return size;
    }

    string next(string& value) {
        Node* node = successor(value);
        return node ? node->value : "";
    }

    string prev(string& value) {
        Node* node = predecessor(value);
        return node ? node->value : "";
    }

    bool exists(string& value) {
        return find(value, root) != nullptr;
    }

    void insert(string& value) {
        if (exists(value))
            return;
        size++;
        root = insert(value, root);
    }

    void remove(string& value) {
        if (!exists(value))
            return;
        size--;
        root = remove(value, root);
    }

    void print() {
        cout << get_size() << " ";
        rec_print(root);
        cout << endl;
    }

private:
    struct Node {
        string value;
        int level;
        Node* left;
        Node* right;

        Node(string &_value) :
                value(_value),
                level(1),
                left(nullptr),
                right(nullptr)
        {}

        Node(string &_value, int _level, Node* _left, Node* _right) :
                value(_value),
                level(_level),
                left(_left),
                right(_right)
        {}
    };

    Node* root;
    size_t size;

    Node* skew(Node* t) {
        if (!t || !t->left)
            return t;
        if (t->left->level == t->level)
            return new Node(t->left->value, t->left->level, t->left->left,
                            new Node(t->value, t->level, t->left->right, t->right));
        return t;
    }

    Node* split(Node* t) {
        if (!t || !t->right || !t->right->right)
            return t;
        if (t->level == t->right->right->level)
            return new Node(t->right->value, t->right->level + 1,
                            new Node(t->value, t->level, t->left, t->right->left), t->right->right);
        return t;
    }

    Node* find(string &value, Node* t) {
        if (!t || value == t->value)
            return t;
        if (value.compare(t->value) < 0)
            return find(value, t->left);
        return find(value, t->right);
    }

    Node* insert(string &value, Node* t) {
        if (!t)
            return new Node(value);
        if (value.compare(t->value) < 0)
            t->left = insert(value, t->left);
        else if (value.compare(t->value) > 0)
            t->right = insert(value, t->right);
        t = skew(t);
        t = split(t);
        return t;
    }

    Node* decreaseLevel(Node* t) {
        int left_level = t->left ? t->left->level : 0;
        int right_level = t->right ? t->right->level : 0;
        int shouldBe = min(left_level, right_level) + 1;
        if (shouldBe < t->level) {
            t->level = shouldBe;
            if (shouldBe < right_level)
                t->right->level = shouldBe;
        }
        return t;
    }

    Node* successor(string &value) {
        Node* current = root;
        Node* next_v = nullptr;
        while (current) {
            if (value.compare(current->value) < 0) {
                next_v = current;
                current = current->left;
            }
            else
                current = current->right;
        }
        return next_v;
    }

    Node* predecessor(string &value) {
        Node* current = root;
        Node* prev_v = nullptr;
        while (current) {
            if (value.compare(current->value) > 0) {
                prev_v = current;
                current = current->right;
            }
            else
                current = current->left;
        }
        return prev_v;
    }

    Node* remove(string &value, Node* t) {
        if (!t)
            return t;
        if (value.compare(t->value) < 0)
            t->left = remove(value, t->left);
        else if (value.compare(t->value) > 0)
            t->right = remove(value, t->right);
        else {
            //value.clear();
            if (!t->left && !t->right)
                return nullptr;
            if (!t->left) {
                string c = next(t->value);
                t->right = remove(c, t->right);
                t->value = c;
            }
            else {
                string c = prev(t->value);
                t->left = remove(c, t->left);
                t->value = c;
            }
        }
        t = decreaseLevel(t);
        t = skew(t);
        t->right = skew(t->right);
        if (t->right)
            t->right->right = skew(t->right->right);
        t = split(t);
        t->right = split(t->right);
        return t;
    }

    void rec_print(Node* t) {
        if (!t)
            return;
        cout << t->value << " ";
        if (t->left)
            rec_print(t->left);
        if (t->right)
            rec_print(t->right);
    }

    void rec_delete(Node* t) {
        if (!t)
            return;
        t->value.clear();
        t->level = 0;
        if (t->left) {
            rec_delete(t->left);
            t->left = nullptr;
        }
        if (t->right) {
            rec_delete(t->right);
            t->right = nullptr;
        }
    }
};

class HashTable {
public:
    explicit HashTable(long long values_range) {
        size = get_size(values_range);
        table.resize(size);
    }

    void put(string &k, string &v) {
        int i = hash(k);
        for (auto j = 0; j < table[i].size(); j++) {
            if (table[i][j].first == k) {
                if (!table[i][j].second.exists(v))
                    table[i][j].second.insert(v);
                return;
            }
        }
        auto tree = AA_Tree();
        tree.insert(v);
        table[i].emplace_back(make_pair(k, tree));
    }

    void get(string &key) {
        int i = hash(key);
        for (auto j = 0; j < table[i].size(); j++) {
            if (table[i][j].first == key) {
                table[i][j].second.print();
                return;
            }
        }
        cout << "0\n";
    }

    void removeAll(string &key) {
        int i = hash(key);
        for (auto j = 0; j < table[i].size(); j++) {
            if (table[i][j].first == key) {
                table[i][j].second.delete_all();
                return;
            }
        }
    }

    void remove(string &key, string &value) {
        int i = hash(key);
        for (auto j = 0; j < table[i].size(); j++) {
            if (table[i][j].first == key) {
                table[i][j].second.remove(value);
                return;
            }
        }
    }

private:
    vector<vector<pair<string, AA_Tree> > > table;
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
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
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
            cin >> v;
            hashTable.remove(k, v);
        }
        else if (com == "get") {
            hashTable.get(k);
        }
        else if (com == "deleteall") {
            hashTable.removeAll(k);
        }
    }
    return 0;
}
