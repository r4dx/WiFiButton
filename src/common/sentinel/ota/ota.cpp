#ifndef UNIT_TEST
#include "ota.h"

#ifdef OTA_ENABLED
#include <ArduinoOTA.h>
#endif

namespace sentinel {
    namespace ota {
        OverTheAirUploadReceiver::OverTheAirUploadReceiver(log::Logger& logger) 
			: logger(logger) { }

		void OverTheAirUploadReceiver::begin() {
#ifdef OTA_ENABLED
			// Port defaults to 8266
			// ArduinoOTA.setPort(8266);

			// Hostname defaults to esp8266-[ChipID]
			// ArduinoOTA.setHostname("myesp8266");

			// No authentication by default
			// ArduinoOTA.setPassword((const char *)"123");

			ArduinoOTA.onStart([this]() {
				this->started = true;
				this->logger.info("Start");
			});

			ArduinoOTA.onEnd([this]() {
				this->started = false;
				this->logger.info("End");
			});

			ArduinoOTA.onProgress([this](unsigned int progress,
				unsigned int total) {
				this->logger.info("Progress: %u%%\r", progress);
			});

			ArduinoOTA.onError([this](ota_error_t error) {
				this->logger.info("Error[%u]: ", error);
				if (error == OTA_AUTH_ERROR) this->logger.info("Auth Failed");
				else if (error == OTA_BEGIN_ERROR) this->logger.info("Begin Failed");
				else if (error == OTA_CONNECT_ERROR) this->logger.info("Connect Failed");
				else if (error == OTA_RECEIVE_ERROR) this->logger.info("Receive Failed");
				else if (error == OTA_END_ERROR) this->logger.info("End Failed");
			});
			ArduinoOTA.begin();
			logger.info("Ready");
#endif
		}

        bool OverTheAirUploadReceiver::process() {
        #ifdef OTA_ENABLED
            ArduinoOTA.handle();
        #endif
            return this->started;
        }
    }
}
#endif