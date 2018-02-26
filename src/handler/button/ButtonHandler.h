#pragma once
#include "conf/Configuration.h"
#include "common/sentinel/logger/Logger.h"
#include <ESP8266HTTPClient.h>

namespace wifi_button {
	namespace handler {
		class ButtonHandler {
		public:
			ButtonHandler(const configuration::Configuration& configuration, sentinel::log::Logger& logger);
			void handle();
		private:
			void addHeaders(HTTPClient& client);
			const configuration::Configuration& configuration;
			sentinel::log::Logger& logger;
		};
	}
}
