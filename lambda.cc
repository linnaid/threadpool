//lambda表达式


//[capture list] (parameter list) -> return type { function body }
//捕获列表（capture list）：用于指定在 lambda 表达式内部可以使用的外部变量。可以按值（=）或按引用（&）捕获；
//参数列表（parameter list）：和普通函数的参数列表类似；
//返回类型（return type）：可以省略，编译器会自动推导；
//函数体（function body）：lambda 表达式要执行的代码；


#include <iostream>

//简单的 lambda 表达式：
int main() {
    // 定义一个简单的lambda表达式
    auto add = [](int a, int b) { return a + b; };
    std::cout << "3 + 5 = " << add(3, 5) << std::endl;
    return 0;
}


//使用捕获列表：
// int main() {
//     int x = 10;
//     // 按值捕获x
//     auto multiplyByX = [x](int a) { return a * x; };
//     std::cout << "5 * 10 = " << multiplyByX(5) << std::endl;

//     // 按引用捕获x
//     auto incrementX = [&x]() { x++; };
//     incrementX();
//     std::cout << "x after increment: " << x << std::endl;
//     return 0;
// }

//在标准库算法中使用 lambda：
// #include <iostream>
// #include <vector>
// #include <algorithm>

// int main() {
//     std::vector<int> numbers = {1, 2, 3, 4, 5};
//     // 使用lambda表达式进行排序
//     std::sort(numbers.begin(), numbers.end(), [](int a, int b) { return a > b; });
//     for (int num : numbers) {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;
//     return 0;
// }

