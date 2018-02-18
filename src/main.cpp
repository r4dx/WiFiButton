#ifndef UNIT_TEST
//#include <vector> // hack to make it compile - https://github.com/esp8266/Arduino/issues/2549

#include <string>
#include <memory>
#include <Arduino.h>
#include "common/sentinel/web/ESPWebServer.h"
#include "conf/configuration.h"
#include "common/sentinel/logger/logger.h"
#include "common/sentinel/ota/ota.h"
#include "common/sentinel/logger/ConsoleFileLoggerWrapper.h"
#include "common/sentinel/time/TimeString.h"
#include "common/sentinel/wifi/WiFiConnection.h"
#include "handler/HealthcheckHandler.h"


sentinel::ota::OverTheAirUploadReceiver* otaReceiver = nullptr;
sentinel::log::Logger* logger;
sentinel::web::IWebServer* web;

void initLogger() {
	Serial.begin(112500);
    logger = new sentinel::log::Logger(Serial, *(new sentinel::time::MillisTimeProvider()));
    logger->setLevel(sentinel::log::DEBUG);
}

void initWiFi() {
	logger->info("Connecting to WiFi");
	sentinel::wifi::WiFiConnection connection(wifi_button::configuration::wifi::SSID, 
		wifi_button::configuration::wifi::PASSWORD, 5, 1000);

	if (!connection.connect()) {
		logger->error("Can't connect to WiFi, restarting!");
		ESP.restart();
	}

	logger->info("Connected, IP is " + connection.getIp());

}

void initWebServer() {
    logger->info("Loading handlers");
	// Will never be deleted!    
	auto healthcheckHandler = new wifi_button::handler::HealthcheckHandler(*logger);

    ESP8266WebServer* server = new ESP8266WebServer(80);
    web = new sentinel::web::ESPWebServer(*server, *logger);
	web->on(*healthcheckHandler);

    logger->info("Starting web server");
    web->start();    
    logger->info("Started successfully");
}

void setup() {
    initLogger();
	initWiFi();
    initWebServer();
}

void loop() {    
    if (otaReceiver == nullptr) {
        logger->info("Initializing Over-the-air update receiver");
		otaReceiver = new sentinel::ota::OverTheAirUploadReceiver(*logger);
		otaReceiver->begin();
		logger->info("Initialized");
		return;
    }

    if (otaReceiver->process())
        return;

    web->process();

    //logger->info("Ping");
    delay(100);
}
#endif