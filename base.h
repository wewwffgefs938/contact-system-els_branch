#pragma once
#ifndef __BASE__
#define __BASE__

#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <conio.h>
#include  <cstdlib>
#include <vector>
#include <thread>
#include <iomanip>

using namespace std;

class Logger {
public:
    // 构造函数
    Logger(const std::string& filename) : originalBuffer(nullptr) {
        logFile.open(filename, std::ios::out | std::ios::app); // 追加模式，确保日志不会被覆盖
        if (!logFile.is_open()) {
            std::cerr << "无法打开日志文件！" << std::endl;
            return;
        }
        originalBuffer = std::cerr.rdbuf(logFile.rdbuf()); // 重定向 cerr
    }

    ~Logger() {
        if (logFile.is_open()) {
            std::cerr.rdbuf(originalBuffer); // 恢复原始 cerr
            logFile.close();
        }
    }

private:
    std::ofstream logFile;
    std::streambuf* originalBuffer;
};


const int version = 1.01;
const string system_name = "contact-saver";


#endif // !__BASE__
