#include <string>
#include <iostream>

struct base {
    virtual std::string msg() const {
        return "base";
    }
};

struct derived {
    std::string msg() const {
        return "derived";
    }
};

int main() {
    try {
        throw derived();
    }
    catch (base const& e) {
        std::cout << e.msg();
    }
}