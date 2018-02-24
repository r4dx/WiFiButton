#ifndef UNIT_TEST
//#include <vector> // hack to make it compile - https://github.com/esp8266/Arduino/issues/2549

#include <string>
#include <memory>
#include <Arduino.h>
#include "common/sentinel/web/ESPWebServer.h"
#include "common/sentinel/logger/logger.h"
#include "common/sentinel/ota/ota.h"
#include "common/sentinel/logger/ConsoleFileLoggerWrapper.h"
#include "common/sentinel/time/TimeString.h"
#include "common/sentinel/wifi/Connection.h"
#include "common/sentinel/wifi/AccessPoint.h"
#include "common/sentinel/wifi/IProvider.h"
#include "common/sentinel/storage/eeprom/EEPROM.h"
#include "handler/healthcheck/HealthcheckHandler.h"
#include "handler/setup/SetupHandler.h"
#include "handler/test/TestHandler.h"
#include "conf/Configuration.h"

sentinel::ota::OverTheAirUploadReceiver* otaReceiver = nullptr;
sentinel::log::Logger* logger;
sentinel::web::IWebServer* web;
std::shared_ptr<wifi_button::configuration::Configuration> configuration;

void initLogger() {
	Serial.begin(112500);
    logger = new sentinel::log::Logger(Serial, *(new sentinel::time::MillisTimeProvider()));
    logger->setLevel(sentinel::log::DEBUG);
}

void initWiFi() {
	logger->info("Connecting to WiFi");
	// N.B. Never destroyed and thus never disconnects!!
	sentinel::wifi::IProvider* connection;
	// N.B. Never destroyed
	sentinel::storage::EEPROM* eeprom = new sentinel::storage::EEPROM(SDA, SCL, 0x50);
	configuration = wifi_button::configuration::Configuration::load(*eeprom);
	if (configuration == nullptr)
		connection = new sentinel::wifi::AccessPoint("WiFiButton");
	else
		connection = new sentinel::wifi::Connection(configuration->ssid, configuration->password, 15, 1000);

	if (!connection->connect()) {
		logger->error("Can't connect to WiFi, restarting!");
		ESP.restart();
	}
	// if AP it's 192.168.4.1
	logger->info("Connected, IP is " + connection->getIp());
}

void initWebServer() {
    logger->info("Loading handlers");
	// Will never be deleted!    
	auto healthcheckHandler = new wifi_button::handler::HealthcheckHandler(*logger);
	auto setupHandler = new wifi_button::handler::SetupHandler(*logger, configuration);
	auto testHandler = new wifi_button::handler::TestHandler(*logger);

    ESP8266WebServer* server = new ESP8266WebServer(80);
    web = new sentinel::web::ESPWebServer(*server, *logger);
	web->on(*healthcheckHandler);
	web->on(*setupHandler);
	web->on(*testHandler);

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