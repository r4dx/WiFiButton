#include "ButtonHandler.h"
#include <string>
#include "common/sentinel/string/Utils.h"
#include "common/sentinel/web/Method.h"

namespace wifi_button {
	namespace handler {
		ButtonHandler::ButtonHandler(const configuration::Configuration& configuration, sentinel::log::Logger& logger) :
			configuration(configuration), 
			logger(logger) { }

		void ButtonHandler::addHeaders(HTTPClient& client) {
			std::string headersString(configuration.headers);
			sentinel::string::replaceAll(headersString, "\r", "");
		
			std::vector<std::string> headers = sentinel::string::split(headersString, "\n");
			for (auto const& header : headers) {
				logger.debug("Parsing config line: " + header);
				std::vector<std::string> nameValue = sentinel::string::split(header, ":");
				if (nameValue.size() != 2)
					continue;
				std::string name = nameValue[0];
				std::string value = nameValue[1];
				client.addHeader(name.c_str(), value.c_str());
				logger.debug("Added header: name='%s', value='%s'", name.c_str(), value.c_str());
			}
		}

		void ButtonHandler::handle() {
			logger.info("Button is pressed");
			HTTPClient client;
			if (!client.begin(configuration.url.c_str())) {
				logger.error("Can't open URL: " + configuration.url);
				return;
			}
			addHeaders(client);
			logger.debug("Sending request");
			int result = client.sendRequest(sentinel::web::methodToString(configuration.method).c_str(), 
				configuration.body.c_str());
			logger.debug("Result is %d", result);
		}
	}
}
