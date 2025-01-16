#include <cstdlib>
#include <iostream>
#include <string>

void mountSecureFS(const std::string& encDir, const std::string& mountDir, const std::string& password) {
    // 构建 securefs 挂载命令
    std::string command = "./securefs mount " + encDir + " " + mountDir + " --password " + password;

    // 执行命令
    int result = std::system(command.c_str());
    if (result == 0) {
        std::cout << "Mounted successfully: " << mountDir << std::endl;
    } else {
        std::cerr << "Failed to mount securefs. Error code: " << result << std::endl;
    }
}

void unmountSecureFS(const std::string& mountDir) {
    // 构建 securefs 卸载命令
    std::string command = "./securefs unmount " + mountDir;

    // 执行命令
    int result = std::system(command.c_str());
    if (result == 0) {
        std::cout << "Unmounted successfully: " << mountDir << std::endl;
    } else {
        std::cerr << "Failed to unmount securefs. Error code: " << result << std::endl;
    }
}

int main() {
    std::string encDir = "/encrypted";
    std::string mountDir = "/mnt/secure";
    std::string password = "your-password";

    // 挂载 securefs
    mountSecureFS(encDir, mountDir, password);

    // 模拟程序运行
    std::cout << "SecureFS mounted. Press Enter to unmount..." << std::endl;
    std::cin.get();

    // 卸载 securefs
    unmountSecureFS(mountDir);

    return 0;
}
