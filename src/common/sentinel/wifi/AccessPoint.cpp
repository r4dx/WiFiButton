#include "AccessPoint.h"
#include <ESP8266WiFi.h>

namespace sentinel {
	namespace wifi {
		bool AccessPoint::connect() {
			WiFi.mode(WIFI_AP_STA);
			connected = WiFi.softAP(SSID.c_str());
			return connected;
		}

		bool AccessPoint::disconnect() {
			if (connected)
				return WiFi.softAPdisconnect(true);
			return false;
		}

		std::string AccessPoint::getIp() const {
			return std::string(WiFi.softAPIP().toString().c_str());
		}

		AccessPoint::AccessPoint(const std::string& SSID) : SSID(SSID) { }

		AccessPoint::~AccessPoint() {
			disconnect();
		}

	}
}