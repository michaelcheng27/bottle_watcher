#include "logger.h"
#include <SPI.h>
#define LOG_LENGTH 64

void Logger::info(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    Logger::log(LogLevel::INFO, fmt, args);
    va_end(args);
}

void Logger::log(const LogLevel logLevel, const char *fmt, va_list args) {
    //  log level is reserved to skip logging in future.
    char buff[LOG_LENGTH];

    const size_t len = vsnprintf(buff, sizeof(buff), fmt, args);

    if (len > LOG_LENGTH) {
        Serial.println("[ERROR] Log is trucated");
    }
    Serial.println(buff);
}
