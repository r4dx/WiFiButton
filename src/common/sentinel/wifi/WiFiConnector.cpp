#include "WiFiConnector.h"
#include <ESP8266WiFi.h>

namespace sentinel {
	namespace wifi {
		WiFiConnector::WiFiConnector(const std::string & SSID, const std::string & password, 
			int attempts, int delayBetweenAttempts = 5000)
			: SSID(SSID), password(password), attempts(attempts), delayBetweenAttempts(delayBetweenAttempts) { }

		bool WiFiConnector::connect() {
			WiFi.mode(WIFI_STA);
			WiFi.begin(SSID.c_str(), password.c_str());
			int current_attempts = attempts;
			while (WiFi.waitForConnectResult() != WL_CONNECTED && current_attempts-- > 0)
				delay(delayBetweenAttempts);

			return true;
		}

		bool WiFiConnector::disconnect() {
			WiFi.disconnect();
		}
		std::string WiFiConnector::getIp() const {
			return std::string(WiFi.localIP().toString().c_str());
		}
	}
}

