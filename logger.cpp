#include "logger.h"

std::ofstream logger::logStream;
std::wofstream logger::logStreamW;
bool logger::isOpen = false;

#pragma region CHAR
//--------------------------------------------------------------------------------------------
bool logger::init(const char* logFilename)
{
    logger::logStream.open(logFilename, std::ofstream::out | std::ofstream::app);
    
    logger::isOpen = logger::logStream.fail() == false;
    return logger::isOpen;
}
//--------------------------------------------------------------------------------------------
// logs message without any header
bool logger::log(const char* message, ...)
{
    char buffer[BUFFER_SIZE];
    short bufferLen;
    bool newLineRequired = false;
    
    if(message == NULL || logger::isOpen == false)
        return false;
    
    va_list args;                                                           
    va_start(args, message);
    
    vsnprintf(buffer, BUFFER_SIZE, message, args);
    bufferLen = strlen(buffer);
    if(bufferLen > 0 && buffer[bufferLen - 1] != '\n')
        newLineRequired = true;

    va_end(args);

    std::time_t t = std::time(nullptr);
    logger::logStream << std::put_time(std::localtime(&t), "%F %T") << " " << buffer;

    if(newLineRequired)
        logger::logStream << std::endl;

    logger::logStream.flush();
    return true;
}
//--------------------------------------------------------------------------------------------
// [DON'T USE] logs message with the given header. it's for internal use only
bool logger::logWithHeader(const char *header, short headerLen, const char* message, va_list args)
{
    char buffer[BUFFER_SIZE];
    short bufferLen;
    bool newLineRequired = false;

    if(header == NULL || logger::isOpen == false)
        return false;
    
    strncpy(buffer, header, BUFFER_SIZE);
    vsnprintf(buffer + headerLen, BUFFER_SIZE - headerLen, message, args);
    bufferLen = strlen(buffer);
    if(bufferLen > 0 && buffer[bufferLen - 1] != '\n')
        newLineRequired = true;

    std::time_t t = std::time(nullptr);
    logger::logStream << std::put_time(std::localtime(&t), "%F %T") << buffer;
    
    if(newLineRequired)
        logger::logStream << std::endl;

    logger::logStream.flush();
    return true;
}
//--------------------------------------------------------------------------------------------
// logs message as error
bool logger::error(const char* message, ...)
{
    if(message == NULL)
        return false;

    va_list args;
    va_start(args, message);

    bool retVal = logger::logWithHeader(HEADER_ERROR, HEADER_LEN, message, args);
    va_end(args);
    
    return retVal;
}
//--------------------------------------------------------------------------------------------
// logs message as error
bool logger::info(const char* message, ...)
{
    if(message == NULL)
        return false;

    va_list args;
    va_start(args, message);

    bool retVal = logger::logWithHeader(HEADER_INFO, HEADER_LEN, message, args);
    va_end(args);
    
    return retVal;
}
//--------------------------------------------------------------------------------------------
// logs message as error
bool logger::success(const char* message, ...)
{
    if(message == NULL)
        return false;

    va_list args;
    va_start(args, message);

    bool retVal = logger::logWithHeader(HEADER_SUCCESS, HEADER_LEN, message, args);
    va_end(args);
    
    return retVal;
}
#pragma endregion CHAR

#pragma region WCHAR_T
//--------------------------------------------------------------------------------------------
bool logger::init(const wchar_t* logFilename)
{
    std::wstring ws(logFilename);
    std::string filename(ws.begin(), ws.end());

    logger::logStreamW.open(filename, std::ofstream::out | std::ofstream::app);
    
    logger::isOpen = logger::logStream.fail() == false;
    return logger::isOpen;
}
//--------------------------------------------------------------------------------------------
// logs message without any header
bool logger::log(const wchar_t* message, ...)
{
    wchar_t buffer[BUFFER_SIZE];
    short bufferLen;
    bool newLineRequired = false;
    
    if(message == NULL || logger::isOpen == false)
        return false;
    
    va_list args;                                                           
    va_start(args, message);
    
    vswprintf(buffer, BUFFER_SIZE, message, args);
    bufferLen = wcsnlen(buffer, BUFFER_SIZE);
    if(bufferLen > 0 && buffer[bufferLen - 1] != L'\n')
        newLineRequired = true;

    va_end(args);

    std::time_t t = std::time(nullptr);
    logger::logStreamW << std::put_time(std::localtime(&t), L"%F %T") << L" " << buffer;

    if(newLineRequired)
        logger::logStreamW << std::endl;
    
    logger::logStreamW.flush();
    return true;
}
//--------------------------------------------------------------------------------------------
// [DON'T USE] logs message with the given header. it's for internal use only
bool logger::logWithHeader(const wchar_t *header, short headerLen, const wchar_t* message, va_list args)
{
    wchar_t buffer[BUFFER_SIZE];
    short bufferLen;
    bool newLineRequired = false;

    if(header == NULL || logger::isOpen == false)
        return false;
    
    wcsncpy(buffer, header, BUFFER_SIZE);
    vswprintf(buffer + headerLen, BUFFER_SIZE - headerLen, message, args);
    bufferLen = wcsnlen(buffer, BUFFER_SIZE);
    if(bufferLen > 0 && buffer[bufferLen - 1] != L'\n')
        newLineRequired = true;

    std::time_t t = std::time(nullptr);
    logger::logStreamW << std::put_time(std::localtime(&t), L"%F %T") << buffer;

    if(newLineRequired)
        logger::logStreamW << std::endl;

    logger::logStreamW.flush();
    return true;
}
//--------------------------------------------------------------------------------------------
// logs message as error
bool logger::error(const wchar_t* message, ...)
{
    if(message == NULL)
        return false;

    va_list args;
    va_start(args, message);

    bool retVal = logger::logWithHeader(HEADER_ERRORW, HEADER_LEN, message, args);
    va_end(args);
    
    return retVal;
}
//--------------------------------------------------------------------------------------------
// logs message as error
bool logger::info(const wchar_t* message, ...)
{
    if(message == NULL)
        return false;

    va_list args;
    va_start(args, message);

    bool retVal = logger::logWithHeader(HEADER_INFOW, HEADER_LEN, message, args);
    va_end(args);
    
    return retVal;
}
//--------------------------------------------------------------------------------------------
// logs message as error
bool logger::success(const wchar_t* message, ...)
{
    if(message == NULL)
        return false;

    va_list args;
    va_start(args, message);

    bool retVal = logger::logWithHeader(HEADER_SUCCESSW, HEADER_LEN, message, args);
    va_end(args);
    
    return retVal;
}
#pragma endregion WCHAR_T

//--------------------------------------------------------------------------------------------
void logger::close()
{
    if(logger::logStream.is_open())
    {
        logger::logStream.flush();
        logger::logStream.close();
    }
    if(logger::logStreamW.is_open())
    {
        logger::logStreamW.flush();
        logger::logStreamW.close();
    }
}
//--------------------------------------------------------------------------------------------
/*std::string getCallerFileName()
{
    std::string file = __FILE__;
    size_t index;
    for (index = file.size(); index > 0; index--)
    {
        if (file[index - 1] == '\\' || file[index - 1] == '/')
            break;
    }
    return file.substr(index);
}*/
//--------------------------------------------------------------------------------------------