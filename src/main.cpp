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
#include "common/sentinel/wifi/Connection.h"
#include "common/sentinel/wifi/AccessPoint.h"
#include "common/sentinel/wifi/IProvider.h"
#include "handler/healthcheck/HealthcheckHandler.h"
#include "handler/setup/SetupHandler.h"

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

	// N.B. Never destroyed and thus never disconnects!!
	sentinel::wifi::IProvider* connection;
	//int random_number = random(0, 2);
	//logger->debug("%i - %s", random_number, random_number == 1 ? "Connecting to WIFI" : "Starting access point");
	//if (random_number == 1)
		connection = new sentinel::wifi::Connection(wifi_button::configuration::wifi::SSID,
			wifi_button::configuration::wifi::PASSWORD, 15, 1000);
	//else
	//	connection = new sentinel::wifi::AccessPoint("WiFiButton");

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
	auto setupHandler = new wifi_button::handler::SetupHandler(*logger);

    ESP8266WebServer* server = new ESP8266WebServer(80);
    web = new sentinel::web::ESPWebServer(*server, *logger);
	web->on(*healthcheckHandler);
	web->on(*setupHandler);

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