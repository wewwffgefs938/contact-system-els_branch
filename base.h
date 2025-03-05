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
    // ���캯��
    Logger(const std::string& filename) : originalBuffer(nullptr) {
        logFile.open(filename, std::ios::out | std::ios::app); // ׷��ģʽ��ȷ����־���ᱻ����
        if (!logFile.is_open()) {
            std::cerr << "�޷�����־�ļ���" << std::endl;
            return;
        }
        originalBuffer = std::cerr.rdbuf(logFile.rdbuf()); // �ض��� cerr
    }

    ~Logger() {
        if (logFile.is_open()) {
            std::cerr.rdbuf(originalBuffer); // �ָ�ԭʼ cerr
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
