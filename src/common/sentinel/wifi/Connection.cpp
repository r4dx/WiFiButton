#include "Connection.h"
#include <ESP8266WiFi.h>

namespace sentinel {
	namespace wifi {
		Connection::Connection(const std::string & SSID, const std::string & password, 
			int attempts, int delayBetweenAttempts = 5000)
			: SSID(SSID), 
			password(password), 
			attempts(attempts), 
			delayBetweenAttempts(delayBetweenAttempts),
			connected(false) { }

		Connection::~Connection() {
			disconnect();
		}

		bool Connection::connect() {
			if (WiFi.isConnected())
				WiFi.disconnect();
			WiFi.mode(WIFI_STA);
			WiFi.begin(SSID.c_str(), password.c_str());
			int current_attempts = attempts;
			while (WiFi.waitForConnectResult() != WL_CONNECTED && current_attempts-- > 0) {
				delay(delayBetweenAttempts);
			}				
			connected = WiFi.waitForConnectResult() == WL_CONNECTED;

			return connected;
		}

		bool Connection::disconnect() {
			if (connected)
				return WiFi.disconnect();
			return false;
		}
		std::string Connection::getIp() const {
			return std::string(WiFi.localIP().toString().c_str());
		}
	}
}

