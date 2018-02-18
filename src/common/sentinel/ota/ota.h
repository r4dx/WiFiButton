#ifndef OTA_H
#define OTA_H

#define OTA_ENABLED 1

#include "../logger/logger.h"
#include <string>

namespace sentinel {
    namespace ota {
        class OverTheAirUploadReceiver {
        public:
            OverTheAirUploadReceiver(log::Logger& logger);
			void begin();
            bool process();

        private:
			log::Logger& logger;
            bool started = false;
        };
    }
}
#endif