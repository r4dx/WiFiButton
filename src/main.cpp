#ifndef UNIT_TEST
//#include <vector> // hack to make it compile - https://github.com/esp8266/Arduino/issues/2549

#include <string>
#include <memory>
#include <WiFiClient.h>
#include <Arduino.h>
#include "common/sentinel/web/ESPWebServer.h"
#include "conf/configuration.h"
#include "common/sentinel/logger/logger.h"
#include "common/sentinel/ota/ota.h"
#include "common/sentinel/logger/ConsoleFileLoggerWrapper.h"
#include "common/sentinel/time/TimeString.h"

sentinel::ota::OverTheAirUploadReceiver* otaReceiver = nullptr;
sentinel::log::ConsoleFileLoggerWrapper* loggerWrapper;
sentinel::web::IWebServer* web;

void initLogger() {
    loggerWrapper = new sentinel::log::ConsoleFileLoggerWrapper(
            std::shared_ptr<std::string>(
                new std::string(
                    sentinel::log::ConsoleFileLoggerWrapper::DefaultLoggerFileName)),
            *(new sentinel::time::MillisTimeProvider()));
    
    loggerWrapper->get().setLevel(sentinel::log::DEBUG);
}

void initWebServer() {
    sentinel::log::Logger& logger = loggerWrapper->get();
    logger.info("Loading handlers");
    
/*
    // Will never be deleted!
    auto getLogHandler = new sentinel::handler::log::GetLogHandler(logger);
    auto removeLogHandler = new sentinel::handler::log::RemoveLogHandler(*loggerWrapper);
    auto browseSDHandler = new sentinel::handler::sd::BrowseSDHandler(logger);
    auto ioExpanderHandler = new sentinel::handler::io_expander::IOExpanderHandler(logger);
	auto pictureHandler = new sentinel::handler::camera::PictureHandler(logger);
*/
    ESP8266WebServer* server = new ESP8266WebServer(80);
    web = new sentinel::web::ESPWebServer(*server, logger);

/*
    web->on(*getLogHandler);
    web->on(*removeLogHandler);
    web->on(*browseSDHandler);
    web->on(*ioExpanderHandler);
	web->on(*pictureHandler);
*/
    logger.info("Starting web server");
    web->start();    
    logger.info("Started successfully");
}

void setup() {
    initLogger();
    initWebServer();
}

void loop() {
    auto logger = loggerWrapper->get();
    
    if (otaReceiver == nullptr) {
        logger.info("Initializing Over-the-air update receiver");
            otaReceiver = new sentinel::ota::OverTheAirUploadReceiver(logger, 
                    wifi_button::configuration::wifi::SSID, 
					wifi_button::configuration::wifi::PASSWORD);
            logger.info("Initialized");
            return;
    }

    if (otaReceiver->process())
        return;

    web->process();

    //logger->info("Ping");
    delay(100);
}
#endif