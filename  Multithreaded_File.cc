// 创建一个结构体表示文件搜索的配置，包括搜索的根目录、搜索的文件类型、最大并发数等。
// 使用多线程并发地递归搜索目录下的文件，找到指定类型的文件并输出文件路径。
// 控制并发数，避免过多的线程占用系统资源。
// 设置最大搜索深度，避免无限制地搜索。
// 可以选择是否跳过指定目录或文件的搜索。

// 需要注意线程安全和资源占用问题，避免死锁、竞争条件等问题。
// 可以为搜索结果添加排序、去重等功能。(可选)


#include <iostream>
#include <vector>
#include <filesystem>

using namespace std;

struct SearchConfig {
    std::string root_path;    // 要搜索的根目录
    std::string file_type;    // 要搜索的文件类型，如 ".txt"、".cpp" 等
    int max_concurrency;      // 最大并发数
    int max_depth;            // 最大搜索深度
    bool skip_hidden;         // 是否跳过隐藏文件或目录
    std::vector<std::string> skip_paths;   // 要跳过的目录或文件的路径
};


void* Initmutex(SearchConfig* a);


std::filesystem::path search(std::string type);
