//
// Created by Tyrese on 2019-08-14.
//

#include <iostream>

#include "Logger.h"

Logger::LogType Logger::mode = LogType::STDOUT;

void Logger::Debug(const char *file, const char *func, int line, std::string msg) {
    std::string out;
    if (msg.empty()) {
        out = "success";
    } else {
        out = msg;
    }
    if (mode == STDOUT) {
#ifndef ANDROID
        std::cout << "[" << file << "][" << func << ":" << line << "] " << out << std::endl;
#else
        __android_log_print(ANDROID_LOG_DEBUG, "bush", "[%s][%s:%d] %s", file, func, line, out.c_str());
#endif

    }
}

void Logger::Error(const char *file, const char *func, int line, std::string msg) {
    std::string out;
    if (msg.empty()) {
        out = "success";
    } else {
        out = msg;
    }
    if (mode == STDOUT) {
#ifndef ANDROID
        std::cerr << "[" << file << "][" << func << ":" << line << "] " << out << std::endl;
#else
        __android_log_print(ANDROID_LOG_ERROR, "bush", "[%s][%s:%d] %s", file, func, line, out.c_str());
#endif
    } else if (mode == FILE) {
//        FileHandler::writeAppendFile(errorLogFileName.c_str(), (unsigned char*)(out.c_str()), out.length());
    }

}

