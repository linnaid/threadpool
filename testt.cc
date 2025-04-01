#include <iostream>

// 递归终止函数
void printArgs() {
    std::cout << std::endl;
}

// 可变参数模板函数
template <typename T, typename... Args>
void printArgs(T first, Args... args) {
    std::cout << first;
    if constexpr (sizeof...(args) > 0) {
        std::cout << ", ";
    }
    printArgs(args...);
}

int main() {
    printArgs(1, 2.5, "hello");
    return 0;
}
