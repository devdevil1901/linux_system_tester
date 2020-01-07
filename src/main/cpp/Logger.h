//
// Created by devdevil on 2019-08-14.
//
#ifndef TEST_LOGGER_H
#define TEST_LOGGER_H

#include <string>
#include <iostream>
#include <stdarg.h>

#if defined(ANDROID)
#include <android/log.h>
#endif

const int MAX_LOG_BUFFER = 4096;

#ifdef DEBUG

#define logging(msg) Logger::Debug(__FILE__, __func__, __LINE__, msg)
#define failing(msg) Logger::Error(__FILE__, __func__, __LINE__, msg)

#else
#define ERROR(...) {}
#define LOG(...) {}
#define SUCCESS(...) {}
#define FAILED(...) {}
#define LOGLINE(...) {}

#define SUCCESSX() {}
#define FAILEDX()  {}
#endif

const std::string logFileName = "log.log";
const std::string errorLogFileName = "error.log";

class Logger {
public:
    enum LogType {
        STDOUT,
        FILE,
        NO
    };
    static LogType mode;
    static void Debug(const char *file, const char *func, int line, std::string msg);
    static void Error(const char *file, const char *func, int line, std::string msg);
};

#endif //TEST_LOGGER_H
