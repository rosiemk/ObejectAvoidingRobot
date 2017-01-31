/**
logging.h
Logging sketch to be run when LOGGING is defined in main aether_robot.ino sketch.
Adapted from author: Miguel Grinberg (Michelino robot)
http://bit.ly/2kkeHwu
*/

#ifdef LOGGING
#pragma once
//logging is enabled
#include <stdarg.h>


  void log(char* format, ...)
  {
    char line[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(line, sizeof(line), format, args);
    va_end(args);
    Serial.print(line);
  }



#else

// logging is disabled
#define log(...)

#endif
