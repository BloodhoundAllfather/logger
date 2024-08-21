#include <stdio.h>
#include "logger.h"

int main()
{
    logger::init("/home/ec2-user/logger.txt");
    
    logger::error("ReadFile failed: %d", 5);
    logger::success("ReadFile was successful: %d", 1024);
    logger::info("Debug enabled");
    logger::log("Entered the SetPrivilege function");
    
    logger::close();
    
    return 0;
}
