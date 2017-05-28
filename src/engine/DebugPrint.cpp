#include <ctime>
#include <cstdio>
#include <iostream>

void debugPrint(const char* format, ...)
{
    char timeFormatted[23];
    std::time_t time = std::time(nullptr);
    strftime(timeFormatted, 23, "[%Y-%m-%d %H:%M:%S] ", std::localtime(&time));

    va_list args;
    fprintf(stdout, timeFormatted);
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    fprintf(stdout, "\n");
}