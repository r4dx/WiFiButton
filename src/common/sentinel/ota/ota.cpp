#ifndef UNIT_TEST
#include "ota.h"

#ifdef OTA_ENABLED
#include <ArduinoOTA.h>
#endif

namespace sentinel {
    namespace ota {
        OverTheAirUploadReceiver::OverTheAirUploadReceiver(log::Logger& logger) {
          #ifdef OTA_ENABLED
          // Port defaults to 8266
          // ArduinoOTA.setPort(8266);

          // Hostname defaults to esp8266-[ChipID]
          // ArduinoOTA.setHostname("myesp8266");

          // No authentication by default
          // ArduinoOTA.setPassword((const char *)"123");

          ArduinoOTA.onStart([&logger, this]() {
            this->started = true;
            logger.info("Start");
          });
          
          ArduinoOTA.onEnd([&logger, this]() {
            this->started = false;
            logger.info("End");
          });
          
          ArduinoOTA.onProgress([&logger](unsigned int progress, 
                  unsigned int total) {
            logger.info("Progress: %u%%\r", progress);
          });
          
          ArduinoOTA.onError([&logger](ota_error_t error) {
            logger.info("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) logger.info("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) logger.info("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) logger.info("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) logger.info("Receive Failed");
            else if (error == OTA_END_ERROR) logger.info("End Failed");
          });
          ArduinoOTA.begin();
          logger.info("Ready");
          logger.info("IP address: ");
          logger.info(WiFi.localIP().toString().c_str());
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