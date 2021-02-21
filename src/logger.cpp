#include "logger.h"

Logger::Logger(int logType)
{
    switch (logType)
    {
    case 0:
        cout << "Initializing console logger" << endl;
        break;
    case 1:

        break;
    default:
        break;
    }
}

Logger::~Logger()
{
}