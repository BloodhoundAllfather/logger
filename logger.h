#ifndef __LOGGER_H__
#define __LOGGER_H__

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>
#include <iostream>
#include <cstdarg>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <cstdlib>

#define BUFFER_SIZE        1024

#define HEADER_ERROR    " [ERROR] "
#define HEADER_INFO     " [INFO ] "
#define HEADER_SUCCESS  " [SUCSS] "
#define HEADER_DEBUG    " [DEBUG] "

#define HEADER_ERRORW   L" [ERROR] "
#define HEADER_INFOW    L" [INFO ] "
#define HEADER_SUCCESSW L" [SUCSS] "
#define HEADER_DEBUGW   L" [DEBUG] "

#define HEADER_LEN   9

//std::string getCallerFileName();
//#define logx(...) logger::log(__FILE__, __LINE__, __VA_ARGS__)

class logger
{
public:
    static std::ofstream logStream;
    static std::wofstream logStreamW;
    static bool isOpen;
    static bool debugEnabled;
    static std::mutex logMutex;
    static std::mutex logMutexW;
    
    static bool init(const char* logFilename, bool debug = false);
    static bool init(const wchar_t* logFilename, bool debug = false);
    
    static bool error(const char* message, ...);
    static bool error(const wchar_t* message, ...);
    
    static bool info(const char* message, ...);
    static bool info(const wchar_t* message, ...);
    
    static bool success(const char* message, ...);    
    static bool success(const wchar_t* message, ...);

    static bool debug(const char* message, ...);    
    static bool debug(const wchar_t* message, ...);
    
    static bool log(const char* message, ...);
    static bool log(const wchar_t* message, ...);
    
    static bool logWithHeader(const char *header, short headerLen, const char* message, va_list args);
    static bool logWithHeader(const wchar_t *header, short headerLen, const wchar_t* message, va_list args);

    static void setDebug(bool debug);

    static void close();
};


#endif