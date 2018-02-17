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
#include "handler/HealthcheckHandler.h"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

sentinel::ota::OverTheAirUploadReceiver* otaReceiver = nullptr;
sentinel::log::Logger* logger;
sentinel::web::IWebServer* web;

void initLogger() {
	Serial.begin(112500);
    logger = new sentinel::log::Logger(Serial, *(new sentinel::time::MillisTimeProvider()));
    
    logger->setLevel(sentinel::log::DEBUG);
}

void initWiFi() {
	logger->info("Booting");
	WiFi.mode(WIFI_STA);
	WiFi.begin(wifi_button::configuration::wifi::SSID, 
		wifi_button::configuration::wifi::PASSWORD);

	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		logger->info(" Connection Failed! Rebooting...");
		delay(5000);
		ESP.restart();
	}

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