// FIA-STLIB.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"


std::string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::ostringstream oss;
    oss << 1900 + ltm->tm_year << '-';
    oss << (ltm->tm_mon < 9 ? "0" : "") << 1 + ltm->tm_mon << '-';
    oss << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday;

    return oss.str();
}

std::string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::ostringstream oss;
    oss << (ltm->tm_hour < 10 ? "0" : "") << ltm->tm_hour << ':';
    oss << (ltm->tm_min < 10 ? "0" : "") << ltm->tm_min << ':';
    oss << (ltm->tm_sec < 10 ? "0" : "") << ltm->tm_sec;

    return oss.str();
}

