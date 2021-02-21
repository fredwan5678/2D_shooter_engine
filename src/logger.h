#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

const int CONSOLE = 0;
const int LOG_FILE = 1;

class Logger
{
private:
    /* data */
public:
    Logger(int logType);
    ~Logger();
};

Logger* makeLogger(int logType)
{
    return new Logger(logType);
}

#endif