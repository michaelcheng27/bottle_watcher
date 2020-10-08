#pragma once
#include <stdarg.h>

enum LogLevel {
    DEBUG = 0,
    INFO = 1,
    ERROR = 2,
    FATAL = 3
};

class Logger {
    public:
    static void log(const LogLevel logLevel, const char *fmt, va_list args);
    static void info(const char *fmt, ...);
};