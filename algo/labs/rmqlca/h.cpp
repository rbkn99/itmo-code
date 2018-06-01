//
// Created by matveich on 12.05.18.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <climits>

using namespace std;

typedef unsigned int ui;
typedef long long ll;

using namespace std;

// once aa tree - forever aa tree!

class AA_Tree {
public:
    AA_Tree() {
        root = nullptr;
        size = 0;
    }

    size_t get_size() {
        return size;
    }

    int next(int value) {
        Node* node = successor(value);
        return node ? node->value : INT_MAX;
    }

    int prev(int value) {
        Node* node = predecessor(value);
        return node ? node->value : INT_MIN;
    }

    bool exists(int value) {
        return find(value, root) != nullptr;
    }

    void insert(int value) {
        if (exists(value))
            return;
        size++;
        root = insert(value, root);
    }

    void remove(int value) {
        if (!exists(value))
            return;
        size--;
        root = remove(value, root);
    }

private:
    struct Node {
        int value;
        int level;
        Node* left;
        Node* right;

        Node(int _value) :
                value(_value),
                level(1),
                left(nullptr),
                right(nullptr)
        {}

        Node(int _value, int _level, Node* _left, Node* _right) :
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

    Node* find(int value, Node* t) {
        if (!t || value == t->value)
            return t;
        if (t->value > value)
            return find(value, t->left);
        return find(value, t->right);
    }

    Node* insert(int value, Node* t) {
        if (!t)
            return new Node(value);
        if (value < t->value)
            t->left = insert(value, t->left);
        else if (value > t->value)
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

    Node* successor(int value) {
        Node* current = root;
        Node* next_v = nullptr;
        while (current) {
            if (value < current->value) {
                next_v = current;
                current = current->left;
            }
            else
                current = current->right;
        }
        return next_v;
    }

    Node* predecessor(int value) {
        Node* current = root;
        Node* prev_v = nullptr;
        while (current) {
            if (value > current->value) {
                prev_v = current;
                current = current->right;
            }
            else
                current = current->left;
        }
        return prev_v;
    }

    Node* remove(int value, Node* t) {
        if (!t)
            return t;
        if (value < t->value)
            t->left = remove(value, t->left);
        else if (value > t->value)
            t->right = remove(value, t->right);
        else {
            if (!t->left && !t->right)
                return nullptr;
            if (!t->left) {
                int c = next(t->value);
                t->right = remove(c, t->right);
                t->value = c;
            }
            else {
                int c = prev(t->value);
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
};

int main() {
    freopen("parking.in", "r", stdin);
    freopen("parking.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    AA_Tree tree;
    for (int i = 0; i < n; i++) {
        tree.insert(i + 1);
    }
    string req;
    int x = 0;
    for (int i = 0; i < m; i++) {
        cin >> req >> x;
        if (req == "enter") {
            auto res = tree.next(x - 1);
            if (res == INT_MAX)
                res = tree.next(0);
            cout << res << endl;
            tree.remove(res);
        }
        else
            tree.insert(x);
    }
    return 0;
}