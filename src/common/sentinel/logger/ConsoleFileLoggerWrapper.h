#ifndef CONSOLEFILELOGGERWRAPPER_H
#define CONSOLEFILELOGGERWRAPPER_H
#include "logger.h"
#include <SD.h>
#include <string>
#include "../stream/DualStreamValve.h"
#include "../time/TimeString.h"
#include <memory>

namespace sentinel {
    namespace log {
        class ConsoleFileLoggerWrapper {
        public:
            ConsoleFileLoggerWrapper(std::shared_ptr<std::string> fileName, 
                    time::ITimeProvider& timeProvider);
            
            virtual ~ConsoleFileLoggerWrapper();
            Logger& get();
            bool erase();
            
            static const char DefaultLoggerFileName[];
        private:  
            File file;
            std::shared_ptr<std::string> fileName;
            time::ITimeProvider& timeProvider;
            
            Logger* logger;
            stream::DualStreamValve* dualStream;
            
            bool openFile();
        };
    }
}

#endif /* CONSOLEFILELOGGERWRAPPER_H */

