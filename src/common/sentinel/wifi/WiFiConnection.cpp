#include "WiFiConnection.h"
#include <ESP8266WiFi.h>

namespace sentinel {
	namespace wifi {
		WiFiConnection::WiFiConnection(const std::string & SSID, const std::string & password, 
			int attempts, int delayBetweenAttempts = 5000)
			: SSID(SSID), 
			password(password), 
			attempts(attempts), 
			delayBetweenAttempts(delayBetweenAttempts),
			connected(false) { }

		WiFiConnection::~WiFiConnection() {
			disconnect();
		}

		bool WiFiConnection::connect() {
			WiFi.mode(WIFI_STA);
			WiFi.begin(SSID.c_str(), password.c_str());
			int current_attempts = attempts;
			while (WiFi.waitForConnectResult() != WL_CONNECTED && current_attempts-- > 0)
				delay(delayBetweenAttempts);
			connected = WiFi.waitForConnectResult() == WL_CONNECTED;

			return connected;
		}

		bool WiFiConnection::disconnect() {
			if (connected)
				WiFi.disconnect();
		}
		std::string WiFiConnection::getIp() const {
			return std::string(WiFi.localIP().toString().c_str());
		}
	}
}

